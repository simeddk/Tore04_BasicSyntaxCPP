#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CStaticMesh_Spawner.generated.h"

class ACStaticMeshBase;

UCLASS()
class THIRDPERSONCPP_API ACStaticMesh_Spawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ACStaticMesh_Spawner();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	UClass* WhatIsClassRef;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACStaticMeshBase> WhatIsTSubClassOf;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TSubclassOf<ACStaticMeshBase> SpawnClasses[4];

private:
	ACStaticMeshBase* SpawnedObjects[4];

};
