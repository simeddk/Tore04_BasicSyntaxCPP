#include "CProperty.h"

ACProperty::ACProperty()
{
	PrimaryActorTick.bCanEverTick = true;

	NumA = 777;
	NumB = 20;
	NumC = 30;

	RealA = 100.1f;
	RealB = 200.2f;
	RealC = 300.3f;
}

void ACProperty::BeginPlay()
{
	Super::BeginPlay();
	
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, GetNameSafe(this));

	FString str;
	str += "NumA : ";
	str += FString::FromInt(NumA);
	str += ", NumB : ";
	str += FString::FromInt(NumB);
	str += ", NumC : ";
	str += FString::FromInt(NumC);

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, str);
}

void ACProperty::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

