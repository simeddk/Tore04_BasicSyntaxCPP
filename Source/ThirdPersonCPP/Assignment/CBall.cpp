#include "CBall.h"

ACBall::ACBall()
{
	RootComponent = MeshComp;
	MeshComp->SetSimulatePhysics(true);
}

void ACBall::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Display, TEXT("Ball is spawned!"));
	SetLifeSpan(30.f);
}

