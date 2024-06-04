#include "CStaticMeshBase_Sphere.h"

ACStaticMeshBase_Sphere::ACStaticMeshBase_Sphere()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> meshAsset(TEXT("/Game/StaticMeshes/SM_Sphere"));
	if (meshAsset.Succeeded())
		MeshComp->SetStaticMesh(meshAsset.Object);
}

