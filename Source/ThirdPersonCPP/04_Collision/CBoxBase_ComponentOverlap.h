#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CBoxBase_ComponentOverlap.generated.h"

class UPointLightComponent;

UCLASS()
class THIRDPERSONCPP_API ACBoxBase_ComponentOverlap : public ACBoxBase
{
	GENERATED_BODY()

public:
	ACBoxBase_ComponentOverlap();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void ComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(VisibleDefaultsOnly)
	UPointLightComponent* PointLightComp;
};
