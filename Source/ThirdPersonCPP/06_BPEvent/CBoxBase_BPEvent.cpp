#include "CBoxBase_BPEvent.h"
#include "Global.h"
#include "CPlayer.h"

void ACBoxBase_BPEvent::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Super::ActorBeginOverlap(OverlappedActor, OtherActor);

	DoSomething();
}

void ACBoxBase_BPEvent::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Super::ActorEndOverlap(OverlappedActor, OtherActor);

	ResetSomething();
}

void ACBoxBase_BPEvent::ResetSomething_Implementation()
{
	ACPlayer* Player = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player)
	{
		FLinearColor DefaultColor = FLinearColor(0.450980, 0.403922, 0.360784);
		Player->SetBodyColor(DefaultColor, DefaultColor);
	}

}
