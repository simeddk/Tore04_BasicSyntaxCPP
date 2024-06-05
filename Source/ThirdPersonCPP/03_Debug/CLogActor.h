#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CLogActor.generated.h"

UCLASS()
class THIRDPERSONCPP_API ACLogActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACLogActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	float RunningTime;
};
