#include "CBoxBase_Delegate.h"

void ACBoxBase_Delegate::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Super::ActorBeginOverlap(OverlappedActor, OtherActor);

	if (OnBoxBeginOverlap.IsBound())
	{
		OnBoxBeginOverlap.Execute();
	}

	if (OnBoxOneParam.IsBound())
	{
		FString Str = OnBoxOneParam.Execute(FLinearColor::MakeRandomColor());
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Str);
	}
}

void ACBoxBase_Delegate::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Super::ActorEndOverlap(OverlappedActor, OtherActor);

	if (OnBoxEndOverlap.IsBound())
	{
		OnBoxEndOverlap.Execute();
	}
}
