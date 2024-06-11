#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CParticles.generated.h"

class UParticleSystem;
class ACBoxBase_Event;

UCLASS()
class THIRDPERSONCPP_API ACParticles : public AActor
{
	GENERATED_BODY()
	
public:	
	ACParticles();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void SpawnEmitter(int32 InIndex);

private:
	UPROPERTY(EditAnywhere, Category = "Particle")
	UParticleSystem* Particles[3];

	UPROPERTY(EditAnywhere, Category = "HasEvent")
	ACBoxBase_Event* HasEventActor;

};
