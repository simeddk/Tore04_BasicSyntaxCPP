#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CCrossHairWidget.generated.h"

UCLASS()
class THIRDPERSONCPP_API UCCrossHairWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnTarget();

	UFUNCTION(BlueprintImplementableEvent)
	void OffTarget();
	
};
