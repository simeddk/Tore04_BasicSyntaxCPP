#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CBoxBase_Chest.generated.h"

class UStaticMeshComponent;
class UMaterialInstanceDynamic;

UCLASS()
class THIRDPERSONCPP_API ACBoxBase_Chest : public ACBoxBase
{
	GENERATED_BODY()

public:
	ACBoxBase_Chest();

protected:
	//@ We will create a Dynamic Material in this step.
	virtual void OnConstruction(const FTransform& Transform) override;
	
public:
	//@ Responds to the player's F key input event. Parameters return value to the outside using Call By Reference.
	void Open(FName& OutKey);
	
	//@ Additional events to the Blueprint when the chest is opened. Only can implement this event via Blueprint
	UFUNCTION(BlueprintImplementableEvent)
	void Open();

private:
	//@ Displays information that you must press f to open this chest.
	virtual void OnBoxBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;

	//@ Mesh components that make up the body and lid of the chest
protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* Lid;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* Bottom;

	//@ Material color value that visually shows the color of the key
	UPROPERTY(EditInstanceOnly, Category = "MaterialParams")
	FLinearColor Emissive;

	//@ Key, players can obtain when opening this chest
	UPROPERTY(EditInstanceOnly, Category = "Key")
	FName Key;


private:
	//@ Dynamic Material to apply the above Emissive effect to.
	UMaterialInstanceDynamic* DynamicMaterial;

	//@ bool flag that will cause the same effect as DoOnce.
	bool bAlreadyOpened;
};
