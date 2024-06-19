#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWeaponWidget.generated.h"

UCLASS()
class THIRDPERSONCPP_API UCWeaponWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnAutoFire();

	UFUNCTION(BlueprintImplementableEvent)
	void OffAutoFire();
	
};
