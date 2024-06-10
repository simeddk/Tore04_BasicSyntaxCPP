#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CBoxBase_Delegate.generated.h"

DECLARE_DELEGATE(FBoxBeginOverlap); //void__()
DECLARE_DELEGATE(FBoxEndOverlap); //void__()
DECLARE_DELEGATE_RetVal_OneParam(FString, FBoxOneParam, FLinearColor); //FString__(FLinearColor)

UCLASS()
class THIRDPERSONCPP_API ACBoxBase_Delegate : public ACBoxBase
{
	GENERATED_BODY()

protected:
	virtual void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	virtual void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor) override;

public:
	FBoxBeginOverlap OnBoxBeginOverlap;
	FBoxEndOverlap OnBoxEndOverlap;
	FBoxOneParam OnBoxOneParam;
	
};
