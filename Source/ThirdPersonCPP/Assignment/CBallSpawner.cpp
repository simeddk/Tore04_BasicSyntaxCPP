#include "CBallSpawner.h"
#include "Kismet/KismetMathLibrary.h"

ACBallSpawner::ACBallSpawner()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetupAttachment(RootComponent);

	SpawnOffset = FVector2D(250, 1000);
}

void ACBallSpawner::SpawnBall()
{
	FTransform transform;

	FVector spawnLocation = GetActorLocation() + GetActorUpVector() * SpawnOffset.Y;
	spawnLocation.Y += UKismetMathLibrary::RandomFloatInRange(-SpawnOffset.X, +SpawnOffset.X);
	transform.SetLocation(spawnLocation);

	GetWorld()->SpawnActor<ACBall>(BallClass, transform);
}

