#include "CAnimInstance.h"
#include "Global.h"
#include "CWeaponInterface.h"
#include "CWeapon.h"

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OnwerPawn)
	{
		Speed = OnwerPawn->GetVelocity().Size2D();
		Direction = CalculateDirection(OnwerPawn->GetVelocity(), OnwerPawn->GetControlRotation());
		Pitch = OnwerPawn->GetBaseAimRotation().Pitch;

		ICWeaponInterface* ImplementedPawn = Cast<ICWeaponInterface>(OnwerPawn);
		if (ImplementedPawn)
		{
			ACWeapon* Weapon = ImplementedPawn->GetWeapon();
			if (Weapon)
			{
				bEquipped =  Weapon->IsEquipped();
				bAiming =  Weapon->IsAiming();
			}
		}
	}
}

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OnwerPawn = TryGetPawnOwner();
}
