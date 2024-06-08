#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CBoxBase_Door.generated.h"

class UStaticMeshComponent;
class USoundCue;

UCLASS()
class THIRDPERSONCPP_API ACBoxBase_Door : public ACBoxBase
{
	GENERATED_BODY()

public:
	ACBoxBase_Door();

protected:
	//@ We will create a Dynamic Material in this step.
	virtual void OnConstruction(const FTransform& Transform) override;

	//@ Used to play the door opening animation effect without a timeline.
	virtual void Tick(float DeltaTime) override;

private:
	//@ If you enter the collider without an input key event, the door will automatically open.
	virtual void OnBoxBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;

protected:
	//@ Mesh components that make up the door frame and door
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* DoorFrame;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* Door;

	//@ display what color key is needed to open this door
	UPROPERTY(EditInstanceOnly, Category = "MaterialParams")
	FLinearColor Color;
	
	//@ Key name required to actually open this door
	UPROPERTY(EditInstanceOnly, Category = "Key")
	FName Key;

	//@ Door yaw degree when fully open
	UPROPERTY(EditInstanceOnly, Category = "Door")
	float MaxOpenedDegree;

	//@ Value to use in the alpha term of the lerp function
	UPROPERTY(EditInstanceOnly, Category = "Door")
	float OpenSpeed;

	UPROPERTY(EditAnywhere, Category = "Door")
	USoundCue* OpenSound;

private:
	UMaterialInstanceDynamic* DynamicMaterials[2];

	//@ Does the actual player have the key to open this door?
	bool bHasPlayerKey;

	//@ For play open sound once
	bool bAlreadyOpened;
};
