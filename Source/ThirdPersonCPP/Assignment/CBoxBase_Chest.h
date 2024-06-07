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
	virtual void OnConstruction(const FTransform& Transform) override;

public:
	void Open(FName& OutKey);

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* Lid;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* Bottom;

	UPROPERTY(EditInstanceOnly, Category = "MaterialParams")
	FLinearColor Emissive;

	UPROPERTY(EditInstanceOnly, Category = "Key")
	FName Key;

private:
	UMaterialInstanceDynamic* DynamicMaterial;
	bool bAlreadyOpened;
};
