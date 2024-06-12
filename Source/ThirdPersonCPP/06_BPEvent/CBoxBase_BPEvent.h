#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CBoxBase_BPEvent.generated.h"

UCLASS()
class THIRDPERSONCPP_API ACBoxBase_BPEvent : public ACBoxBase
{
	GENERATED_BODY()

protected:
	virtual void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	virtual void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor) override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "CPP Custom Event")
	void DoSomething();

	UFUNCTION(BlueprintNativeEvent, Category = "CPP Custom Event")
	void ResetSomething();
};
