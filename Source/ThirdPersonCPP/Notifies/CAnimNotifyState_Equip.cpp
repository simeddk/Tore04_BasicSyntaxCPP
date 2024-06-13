#include "CAnimNotifyState_Equip.h"
#include "CWeaponInterface.h"
#include "CWeapon.h"

FString UCAnimNotifyState_Equip::GetNotifyName_Implementation() const
{
	return "Equip";
}

void UCAnimNotifyState_Equip::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp->GetOwner() == nullptr) return;

	ICWeaponInterface* ImplementedOwner = Cast<ICWeaponInterface>(MeshComp->GetOwner());
	if (ImplementedOwner == nullptr) return;

	ACWeapon* Weapon = ImplementedOwner->GetWeapon();
	if (Weapon == nullptr) return;
	
	Weapon->Begin_Equip();
}

void UCAnimNotifyState_Equip::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (MeshComp->GetOwner() == nullptr) return;

	ICWeaponInterface* ImplementedOwner = Cast<ICWeaponInterface>(MeshComp->GetOwner());
	if (ImplementedOwner == nullptr) return;

	ACWeapon* Weapon = ImplementedOwner->GetWeapon();
	if (Weapon == nullptr) return;

	Weapon->End_Equip();
}
