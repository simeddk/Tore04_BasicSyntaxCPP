#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CCubes.generated.h"

class UStaticMeshComponent;
class UMaterialInstanceDynamic;

UCLASS()
class THIRDPERSONCPP_API ACCubes : public AActor
{
	GENERATED_BODY()
	
public:	
	ACCubes();

protected:
	virtual void BeginPlay() override;

private:
	void Drop(int32 InIndex, FLinearColor InColor);

private:
	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* RootComp;

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* MeshComp[3];

private:
	UMaterialInstanceDynamic* DynamicMaterial[3];
	FVector OriginLocation[3];
};
