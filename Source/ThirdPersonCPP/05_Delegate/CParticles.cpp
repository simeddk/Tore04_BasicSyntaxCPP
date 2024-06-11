#include "CParticles.h"
#include "Global.h"
#include "CBoxBase_Event.h"

ACParticles::ACParticles()
{

}

void ACParticles::BeginPlay()
{
	Super::BeginPlay();

	if (ensure(HasEventActor))
	{
		HasEventActor->OnEventBeginOverlap.AddUFunction(this, "SpawnEmitter");
	}

}

void ACParticles::SpawnEmitter(int32 InIndex)
{
	if (ensure(Particles[InIndex]))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particles[InIndex], GetActorLocation());
	}
}
