#include "CDoor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "CPlayer.h"

ACDoor::ACDoor()
{
	BoxComp->SetRelativeLocation(FVector(0, 0, 100));

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
}

void ACDoor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UMaterialInstanceConstant* MaterialAsset = Cast<UMaterialInstanceConstant>(StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("/Game/Assignment/Door/Materials/MI_Frame")));
	if (MaterialAsset)
	{
		DynamicMaterial = UMaterialInstanceDynamic::Create(MaterialAsset, this);
		DoorFrame->SetMaterial(0, DynamicMaterial);
	}

	DynamicMaterial->SetVectorParameterValue("Color", Color);
}

void ACDoor::OnBoxBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Super::OnBoxBeginOverlap(OverlappedActor, OtherActor);

	ACPlayer* Player = Cast<ACPlayer>(OtherActor);
	if (Player)
	{
		for (const FName& key : Player->GetHasKeys())
		{
			if (Key == key)
			{
				Door->SetRelativeRotation(FRotator(0, 90, 0));
			}
		}
	}

}