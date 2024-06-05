#include "CStaticMeshBase.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

ACStaticMeshBase::ACStaticMeshBase()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	SetRootComponent(MeshComp);

	ConstructorHelpers::FObjectFinder<UStaticMesh> meshAsset(TEXT("/Game/StaticMeshes/SM_Cube"));

	if (meshAsset.Succeeded())
		MeshComp->SetStaticMesh(meshAsset.Object);
}

void ACStaticMeshBase::BeginPlay()
{
	Super::BeginPlay();
	
	UMaterialInstanceConstant* materialAsset = Cast<UMaterialInstanceConstant>(StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("/Game/Materials/MI_StaticMesh")));
	
	if (materialAsset)
	{
		DynamicMaterial = UMaterialInstanceDynamic::Create(materialAsset, this);
		MeshComp->SetMaterial(0, DynamicMaterial);
	}
	
	UKismetSystemLibrary::K2_SetTimer(this, "UpdateParameters", 1.f, true);
}

void ACStaticMeshBase::UpdateParameters()
{
	FLinearColor RandomColor;
	RandomColor.R = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
	RandomColor.G = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
	RandomColor.B = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
	//RandomColor = FLinearColor::MakeRandomColor();
	RandomColor.A = 1.f;
	DynamicMaterial->SetVectorParameterValue("BaseColor", RandomColor);

	DynamicMaterial->SetScalarParameterValue("Metallic", RandomColor.R);
	DynamicMaterial->SetScalarParameterValue("Roughness", RandomColor.G);
}
