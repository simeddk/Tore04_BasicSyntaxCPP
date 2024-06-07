#include "CBoxBase_Chest.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

ACBoxBase_Chest::ACBoxBase_Chest()
{
	Emissive = FLinearColor(10, 0, 0);

	Lid = CreateDefaultSubobject<UStaticMeshComponent>("Lid");
	Lid->SetupAttachment(RootComp);

	Bottom = CreateDefaultSubobject<UStaticMeshComponent>("Bottom");
	Bottom->SetupAttachment(RootComp);

	ConstructorHelpers::FObjectFinder<UStaticMesh> LidAsset(TEXT("/Game/Assignment/Chest/SM_ChestTop"));
	if (LidAsset.Succeeded())
	{
		Lid->SetStaticMesh(LidAsset.Object);
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh> BottomAsset(TEXT("/Game/Assignment/Chest/SM_ChestBottom"));
	if (BottomAsset.Succeeded())
	{
		Bottom->SetStaticMesh(BottomAsset.Object);
	}

	Lid->SetRelativeLocation(FVector(-140, 0, -30));
	Bottom->SetRelativeLocation(FVector(-140, 0, -30));
}

void ACBoxBase_Chest::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UMaterialInstanceConstant* MaterialAsset = Cast<UMaterialInstanceConstant>(StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("/Game/Assignment/Chest/MI_Chest")));
	if (MaterialAsset)
	{
		DynamicMaterial = UMaterialInstanceDynamic::Create(MaterialAsset, this);
		Lid->SetMaterial(0, DynamicMaterial);
		Bottom->SetMaterial(0, DynamicMaterial);
	}

	DynamicMaterial->SetVectorParameterValue("Emissive", Emissive);
}

void ACBoxBase_Chest::Open(FName& OutKey)
{
	if (bAlreadyOpened == false)
	{
		bAlreadyOpened = true;
		Lid->SetRelativeRotation(FRotator(110, 0, 0));

		OutKey = Key;
	}
}
