#include "CWeapon.h"
#include "Global.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/DecalComponent.h"
#include "GameFramework/Character.h"
#include "Sound/SoundCue.h"
#include "Materials/MaterialInstanceConstant.h"
#include "CWeaponInterface.h"
#include "CPlayer.h"
#include "CBullet.h"

static TAutoConsoleVariable<bool> CVarDebugLine(TEXT("Tore.DrawDebugLine"), false, TEXT("Enable Draw Aim Line"), ECVF_Cheat);

ACWeapon::ACWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	FireInterval = 0.1f;
	PitchSpeed = 0.25f;
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

	ConstructorHelpers::FClassFinder<UCameraShake> CameraShakeClassAsset(TEXT("/Game/BP_FireShake"));
	if (CameraShakeClassAsset.Succeeded())
	{
		CameraShakeClass = CameraShakeClassAsset.Class;
	}

	ConstructorHelpers::FClassFinder<ACBullet> BulletClassAsset(TEXT("/Game/BP_CBullet"));
	if (BulletClassAsset.Succeeded())
	{
		BulletClass = BulletClassAsset.Class;
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

	if (bAiming == false) return;

	ICWeaponInterface* ImplementedActor = Cast<ICWeaponInterface>(OwnerCharacter);
	if (ImplementedActor == nullptr) return;

	FVector Start, End, Direction;
	ImplementedActor->GetAimInfo(Start, End, Direction);

	bool bDrawDebug = CVarDebugLine.GetValueOnGameThread();
	if (bDrawDebug)
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, -1, 0, 2.f);
	}

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(OwnerCharacter);

	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility, Params))
	{
		if (Hit.Component->IsSimulatingPhysics())
		{
			ImplementedActor->OnTarget();
			return;
		}
	}

	ImplementedActor->OffTarget();
	
}

void ACWeapon::ToggleAutoFire()
{
	bAutoFire = !bAutoFire;
}

void ACWeapon::Begin_Aiming()
{
	bAiming = true;
}

void ACWeapon::End_Aiming()
{
	bAiming = false;
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

void ACWeapon::Begin_Fire()
{
	if (bEquipped == false) return;
	if (bEquipping == true) return;
	if (bAiming == false) return;
	if (bFiring == true) return;

	bFiring = true;
	CurrentPitch = 0.f;

	if (bAutoFire)
	{
		GetWorld()->GetTimerManager().SetTimer(AutoTimerHandle, this, &ACWeapon::Firing, FireInterval, true, 0.f);
		return;
	}

	Firing();
}

void ACWeapon::End_Fire()
{
	bFiring = false;

	if (bAutoFire)
	{
		GetWorld()->GetTimerManager().ClearTimer(AutoTimerHandle);
	}
}

void ACWeapon::Firing()
{
	ACPlayer* Player = Cast<ACPlayer>(OwnerCharacter);
	if (Player)
	{
		APlayerController* PC = Player->GetController<APlayerController>();

		if (CameraShakeClass)
		{
			PC->PlayerCameraManager->PlayCameraShake(CameraShakeClass);
		}
	}

	ICWeaponInterface* ImplementedActor = Cast<ICWeaponInterface>(OwnerCharacter);
	if (ImplementedActor == nullptr) return;

	FVector Start, End, Direction;
	ImplementedActor->GetAimInfo(Start, End, Direction);

	FVector MuzzleLocation = MeshComp->GetSocketLocation("MuzzleFlash");
	if (BulletClass)
	{
		GetWorld()->SpawnActor<ACBullet>(BulletClass, MuzzleLocation, Direction.Rotation());
	}

	if (MuzzleParticle)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleParticle, MeshComp, "MuzzleFlash");
	}

	if (EjectParticle)
	{
		UGameplayStatics::SpawnEmitterAttached(EjectParticle, MeshComp, "EjectBullet");
	}

	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, MuzzleLocation);
	}

	CurrentPitch -= PitchSpeed * GetWorld()->GetDeltaSeconds();
	if (CurrentPitch > -PitchSpeed)
	{
		OwnerCharacter->AddControllerPitchInput(CurrentPitch);
	}

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(OwnerCharacter);

	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility, Params))
	{
		FVector ImpactLocation = Hit.ImpactPoint;
		FRotator ImpactRotation = Hit.ImpactNormal.Rotation();
		if (DecalMaterial)
		{
			UDecalComponent* DecalComp = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalMaterial, FVector(5), ImpactLocation, ImpactRotation, 5.f);
			DecalComp->SetFadeScreenSize(0);
		}

		if (ImpactParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, ImpactLocation, ImpactRotation);
		}

		if (Hit.Component->IsSimulatingPhysics())
		{
			Direction = Hit.Actor->GetActorLocation() - OwnerCharacter->GetActorLocation();
			Direction.Normalize();

			Hit.Component->AddImpulseAtLocation(Direction * 3000.f, OwnerCharacter->GetActorLocation());
		}
	}
}