#include "CWeapon.h"
#include "Global.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"

ACWeapon::ACWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	HolsterSocket = "Holster_AR4";
	HandSocket = "Hand_AR4";

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/Weapons/Meshes/AR4/SK_AR4"));
	if (MeshAsset.Succeeded())
	{
		MeshComp->SetSkeletalMesh(MeshAsset.Object);
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> EquipMontageAsset(TEXT("/Game/Character/Animations/AR4/Equip_Montage"));
	if (EquipMontageAsset.Succeeded())
	{
		EquipMontage = EquipMontageAsset.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> UnequipMontageAsset(TEXT("/Game/Character/Animations/AR4/Unequip_Montage"));
	if (UnequipMontageAsset.Succeeded())
	{
		UnequipMontage = UnequipMontageAsset.Object;
	}
}

void ACWeapon::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	
	if (OwnerCharacter)
	{
		AttachToComponent
		(
			OwnerCharacter->GetMesh(),
			FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
			HolsterSocket
		);
	}
}

void ACWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACWeapon::Equip()
{
	if (bEquipping == true) return;
	if (bEquipped == true) return;

	bEquipping = true;

	OwnerCharacter->PlayAnimMontage(EquipMontage);
}

void ACWeapon::Begin_Equip()
{
	bEquipped = true;

	AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		HandSocket
	);
}

void ACWeapon::End_Equip()
{
	bEquipping = false;
}

void ACWeapon::Unequip()
{
	if (bEquipping == true) return;
	if (bEquipped == false) return;

	bEquipping = true;

	OwnerCharacter->PlayAnimMontage(UnequipMontage);
}

void ACWeapon::Begin_Unequip()
{
	bEquipped = false;

	AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		HolsterSocket
	);
}

void ACWeapon::End_Unequip()
{
	bEquipping = false;
}
//Todo. ANS_Unequip

