#include "CBoxBase_Door.h"
#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "CPlayer.h"

ACBoxBase_Door::ACBoxBase_Door()
{
	//@ Although it was not present in the parent class, it must be activated because the Tick must be used here.
	PrimaryActorTick.bCanEverTick = true;

	//@ Basic object assignment and property granting
	MaxOpenedDegree = 120.f;
	Color = FLinearColor::White;
	OpenSpeed = 5.f;

	BoxComp->SetRelativeLocation(FVector(0, 0, 100));
	TextRenderComp->SetRelativeLocation(FVector(0, 0, 220));

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>("DoorFrame");
	DoorFrame->SetupAttachment(RootComp);
	
	Door = CreateDefaultSubobject<UStaticMeshComponent>("Door");
	Door->SetupAttachment(DoorFrame);
	Door->SetRelativeLocation(FVector(0, 45, 0));

	ConstructorHelpers::FObjectFinder<UStaticMesh> doorFrameAsset(TEXT("/Game/Assignment/Door/Props/SM_DoorFrame"));
	if (doorFrameAsset.Succeeded())
	{
		DoorFrame->SetStaticMesh(doorFrameAsset.Object);
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh> doorAsset(TEXT("/Game/Assignment/Door/Props/SM_Door"));
	if (doorAsset.Succeeded())
	{
		Door->SetStaticMesh(doorAsset.Object);
	}

	ConstructorHelpers::FObjectFinder<USoundCue> soundAsset(TEXT("/Engine/EditorSounds/GamePreview/PossessPlayer_Cue"));
	if (soundAsset.Succeeded())
	{
		OpenSound = soundAsset.Object;
	}
}

void ACBoxBase_Door::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	//@ Create Dynamic Material and set to MeshComp
	UMaterialInstanceConstant* MaterialAsset = Cast<UMaterialInstanceConstant>(StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("/Game/Assignment/Door/Materials/MI_Frame")));
	if (MaterialAsset)
	{
		DynamicMaterials[0] = UMaterialInstanceDynamic::Create(MaterialAsset, this);
		DoorFrame->SetMaterial(0, DynamicMaterials[0]);
	}

	MaterialAsset = Cast<UMaterialInstanceConstant>(StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("/Game/Assignment/Door/Materials/MI_Door")));
	if (MaterialAsset)
	{
		DynamicMaterials[1] = UMaterialInstanceDynamic::Create(MaterialAsset, this);
		Door->SetMaterial(0, DynamicMaterials[1]);
	}

	for (const auto& DM : DynamicMaterials)
	{
		DM->SetVectorParameterValue("Color", Color);
	}
}

void ACBoxBase_Door::OnBoxBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Super::OnBoxBeginOverlap(OverlappedActor, OtherActor);

	//@ Assuming the player has the key, this is a completely automatic door.
	ACPlayer* Player = Cast<ACPlayer>(OtherActor);
	if (Player)
	{
		//@ If the player holds the key, set bHasPlayerKey to true.
		for (const FName& keyIterator : Player->GetHasKeys())
		{
			if (Key == keyIterator)
			{
				//@ Play Sound Once
				if (OpenSound && bAlreadyOpened == false)
				{
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), OpenSound, GetActorLocation());
					bAlreadyOpened = true;
				}

				//@ Flag for warn message
				bHasPlayerKey = true;
				break;
			}
		}

		//@ If don't have a key, be warned.
		if (bHasPlayerKey == false)
		{
			FString message = "You don't have a " + Key.ToString() + " key";
			DrawDebugString(GetWorld(), FVector(0, 0, 50), message, this, FColor::White, 2, true, 1.25f);
		}
	}

}

void ACBoxBase_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator CurrRotation = Door->GetRelativeRotation();

	//@ The lerp formula below doesn't need to perform infinite checks.
	if (FMath::IsNearlyEqual(CurrRotation.Yaw, -MaxOpenedDegree, 2.f))
	{
		return;
	}

	//@ Executes a boring and obvious lerp.
	if (bHasPlayerKey)
	{
		Door->SetRelativeRotation(FMath::Lerp(CurrRotation, FRotator(0, -MaxOpenedDegree, 0), OpenSpeed * DeltaTime));
	}
}