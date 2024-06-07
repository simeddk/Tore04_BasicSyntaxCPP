#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CDoor.generated.h"

class UStaticMeshComponent;

UCLASS()
class THIRDPERSONCPP_API ACDoor : public ACBoxBase
{
	GENERATED_BODY()

public:
	ACDoor();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

private:
	virtual void OnBoxBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* DoorFrame;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* Door;

	UPROPERTY(EditInstanceOnly, Category = "MaterialParams")
	FLinearColor Color;
	
	UPROPERTY(EditInstanceOnly, Category = "Key")
	FName Key;

private:
	UMaterialInstanceDynamic* DynamicMaterial;
};
