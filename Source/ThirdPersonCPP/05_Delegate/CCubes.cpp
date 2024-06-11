#include "CCubes.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "CBoxBase_Multicast.h"

ACCubes::ACCubes()
{
	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	RootComponent = RootComp;

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StaticMeshes/SM_Cube"));

	for (int32 i = 0; i < 3; i++)
	{
		FString Str;
		Str.Append("MeshComp");
		Str.Append(FString::FromInt(i + 1));
		MeshComp[i] = CreateDefaultSubobject<UStaticMeshComponent>(FName(Str));
		MeshComp[i]->SetupAttachment(RootComp);

		MeshComp[i]->SetRelativeLocation(FVector(0, i * 150, 0));
		MeshComp[i]->SetSimulatePhysics(false);

		if (MeshAsset.Succeeded())
		{
			MeshComp[i]->SetStaticMesh(MeshAsset.Object);
		}
	}
}

void ACCubes::BeginPlay()
{
	Super::BeginPlay();
	
	UObject* ContentAsset = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("/Game/Materials/MI_StaticMesh"));
	UMaterialInstanceConstant* MaterialAsset = Cast<UMaterialInstanceConstant>(ContentAsset);

	for (int32 i = 0; i < 3; i++)
	{
		if (MaterialAsset)
		{
			DynamicMaterial[i] = UMaterialInstanceDynamic::Create(MaterialAsset, nullptr);
			MeshComp[i]->SetMaterial(0, DynamicMaterial[i]);

			FTransform WorldTranform = MeshComp[i]->GetComponentToWorld();
			OriginLocation[i] = WorldTranform.GetLocation();
		}
	}
	
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACBoxBase_Multicast::StaticClass(), actors);
	
	if (actors.Num() < 1)
	{
		return;
	}

	ACBoxBase_Multicast* Trigger = Cast<ACBoxBase_Multicast>(actors[0]);
	if (Trigger)
	{
		Trigger->OnMulticastBeginOverlap.AddUObject(this, &ACCubes::Drop);
	}
}

void ACCubes::Drop(int32 InIndex, FLinearColor InColor)
{
	CLog::Print("InIndex : " + FString::FromInt(InIndex));

	for (int32 i = 0; i < 3; i++)
	{
		DynamicMaterial[i]->SetVectorParameterValue("BaseColor", FLinearColor::White);
		MeshComp[i]->SetSimulatePhysics(false);
		MeshComp[i]->SetWorldLocation(OriginLocation[i]);
	}

	MeshComp[InIndex]->SetSimulatePhysics(true);
	DynamicMaterial[InIndex]->SetVectorParameterValue("BaseColor", InColor);
}

