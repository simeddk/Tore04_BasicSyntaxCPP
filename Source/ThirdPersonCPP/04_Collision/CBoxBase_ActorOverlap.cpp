#include "CBoxBase_ActorOverlap.h"
#include "Global.h"

void ACBoxBase_ActorOverlap::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACBoxBase_ActorOverlap::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Super::ActorBeginOverlap(OverlappedActor, OtherActor);

	CLog::Print("OtherActor : " + OtherActor->GetActorLabel());
}