#include "CStaticMeshBase.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/KismetSystemLibrary.h"

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
	//Todo.
	//DynamicMaterial->SetVectorParameterValue("BaseColor", );
}
