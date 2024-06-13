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
		
		ICWeaponInterface* ImplementedPawn = Cast<ICWeaponInterface>(OnwerPawn);
		if (ImplementedPawn)
		{
			ACWeapon* Weapon = ImplementedPawn->GetWeapon();
			if (Weapon)
			{
				bEquipped =  Weapon->IsEquipped();
			}
		}
	}
}

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OnwerPawn = TryGetPawnOwner();
}
