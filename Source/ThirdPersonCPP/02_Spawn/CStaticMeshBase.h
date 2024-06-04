#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CStaticMeshBase.generated.h"

UCLASS()
class THIRDPERSONCPP_API ACStaticMeshBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ACStaticMeshBase();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void UpdateParameters();

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	UMaterialInstanceDynamic* DynamicMaterial;
};
