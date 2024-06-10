#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPointLights.generated.h"

class UPointLightComponent;

UCLASS()
class THIRDPERSONCPP_API ACPointLights : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPointLights();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnLights();

	UFUNCTION()
	void OffLights();

	UFUNCTION()
	FString OnRandomLight(FLinearColor InColor);

private:
	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* RootComp;

	UPROPERTY(VisibleDefaultsOnly)
	UPointLightComponent* PointLightComp1;

	UPROPERTY(VisibleDefaultsOnly)
	UPointLightComponent* PointLightComp2;
};
