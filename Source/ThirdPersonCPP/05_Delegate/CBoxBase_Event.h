#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CBoxBase_Event.generated.h"


UCLASS()
class THIRDPERSONCPP_API ACBoxBase_Event : public ACBoxBase
{
	GENERATED_BODY()
	
public:
	DECLARE_EVENT_OneParam(ACBoxBase_Event, FEventBeginOverlap, int32);

	FEventBeginOverlap OnEventBeginOverlap;

protected:
	virtual void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
};
