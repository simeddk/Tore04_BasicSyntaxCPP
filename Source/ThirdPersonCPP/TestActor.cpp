#include "TestActor.h"

ATestActor::ATestActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Actor = this;
	//GLog->Log(Actor->GetName());
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Actor->GetName());

}

void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	
	GLog->Log(Actor->GetActorLocation().ToString());
}

void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

