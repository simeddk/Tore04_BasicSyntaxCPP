#include "CLineTrace.h"
#include "Global.h"
#include "Engine/StaticMeshActor.h"
#include "CPlayer.h"

ACLineTrace::ACLineTrace()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACLineTrace::BeginPlay()
{
	Super::BeginPlay();
	
	OnLineTraced.AddDynamic(this, &ACLineTrace::Ragdoll);
}

void ACLineTrace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Start = Vertices[0]->GetActorLocation();
	FVector End = Vertices[1]->GetActorLocation();

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(Vertices[0]);
	IgnoreActors.Add(Vertices[1]);

	FHitResult Hit;

	if (UKismetSystemLibrary::LineTraceSingleByProfile
	(
		GetWorld(),
		Start,
		End,
		"Pawn",
		false,
		IgnoreActors,
		EDrawDebugTrace::ForOneFrame,
		Hit,
		true
	))
	{
		if (OnLineTraced.IsBound())
		{
			OnLineTraced.Broadcast(Hit.GetActor(), FLinearColor(0, 1, 1));
		}
	}
}

void ACLineTrace::Ragdoll(AActor* InActor, FLinearColor InColor)
{
	ACPlayer* Player = Cast<ACPlayer>(InActor);
	if (Player)
	{
		Player->GetMesh()->SetSimulatePhysics(true);
		Player->GetMesh()->SetCollisionProfileName("Ragdoll");
		Player->GetMesh()->AddImpulse(Player->GetActorUpVector() * 4000.f);
	}
}

