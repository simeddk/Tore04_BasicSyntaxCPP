#include "CAnimInstance.h"
#include "Global.h"

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OnwerPawn)
	{
		Speed = OnwerPawn->GetVelocity().Size2D();
	}
}

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OnwerPawn = TryGetPawnOwner();
}
