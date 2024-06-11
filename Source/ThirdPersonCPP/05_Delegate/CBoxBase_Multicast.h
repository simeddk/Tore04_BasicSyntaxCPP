#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CBoxBase_Multicast.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FMulticastBeginOverlap, int32, FLinearColor);

UCLASS()
class THIRDPERSONCPP_API ACBoxBase_Multicast : public ACBoxBase
{
	GENERATED_BODY()

protected:
	virtual void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;

public:
	FMulticastBeginOverlap OnMulticastBeginOverlap;
	
};
