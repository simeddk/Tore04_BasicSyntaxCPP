#include "CPlayer.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "CAnimInstance.h"
#include "CWeapon.h"

ACPlayer::ACPlayer()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(GetCapsuleComponent());
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 60));
	SpringArmComp->TargetArmLength = 200.f;
	SpringArmComp->bDoCollisionTest = false;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 400.f;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	ConstructorHelpers::FClassFinder<UCAnimInstance> AnimInstanceClass(TEXT("/Game/ABP_CPlayer"));
	if (AnimInstanceClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClass.Class);
	}
}

void ACPlayer::ChangeSpeed(float InMoveSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = InMoveSpeed;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	BodyMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(0), this);
	LogoMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(1), this);

	GetMesh()->SetMaterial(0, BodyMaterial);
	GetMesh()->SetMaterial(1, LogoMaterial);

	FActorSpawnParameters SpawnParam;
	SpawnParam.Owner = this;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//Todo. BP Class Ref
	Weapon = GetWorld()->SpawnActor<ACWeapon>(SpawnParam);
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &ACPlayer::OnSprint);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ACPlayer::OffSprint);

	PlayerInputComponent->BindAction("Rifle", EInputEvent::IE_Pressed, this, &ACPlayer::ToggleEquip);
}

void ACPlayer::OnMoveForward(float Axis)
{
	FRotator ControlRotation = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(ControlRotation).GetForwardVector();

	AddMovementInput(direction, Axis);
}

void ACPlayer::OnMoveRight(float Axis)
{
	FRotator ControlRotation = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(ControlRotation).GetRightVector();

	AddMovementInput(direction, Axis);
}

void ACPlayer::OnSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void ACPlayer::OffSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
}

void ACPlayer::ToggleEquip()
{
	if (Weapon == nullptr) return;

	if (Weapon->IsEquipped())
	{
		Weapon->Unequip();
		return;
	}

	Weapon->Equip();
	
}

void ACPlayer::SetBodyColor(FLinearColor InBodyColor, FLinearColor InLogoColor)
{
	BodyMaterial->SetVectorParameterValue("BodyColor", InBodyColor);
	LogoMaterial->SetVectorParameterValue("BodyColor", InLogoColor);
}

