#include "CSpotLights.h"
#include "Global.h"
#include "Components/SpotLightComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "CBoxBase_Multicast.h"

ACSpotLights::ACSpotLights()
{
	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	RootComponent = RootComp;

	for (int32 i = 0; i < 3; i++)
	{
		FString Str;
		Str.Append("SpotLightComp");
		Str.Append(FString::FromInt(i + 1));

		SpotLightComp[i] = CreateDefaultSubobject<USpotLightComponent>(FName(Str));
		SpotLightComp[i]->SetupAttachment(RootComp);
		SpotLightComp[i]->SetRelativeLocation(FVector(0, i * 150, 0));
		SpotLightComp[i]->SetRelativeRotation(FRotator(-90, 0, 0));

		SpotLightComp[i]->Intensity = 1e+5f;
		SpotLightComp[i]->OuterConeAngle = 25.f;
	}
}

void ACSpotLights::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACBoxBase_Multicast::StaticClass(), actors);
	
	if (actors.Num() < 1)
	{
		return;
	}

	ACBoxBase_Multicast* Trigger = Cast<ACBoxBase_Multicast>(actors[0]);
	if (Trigger)
	{
		Trigger->OnMulticastBeginOverlap.AddUObject(this, &ACSpotLights::OnLight);
	}
}

void ACSpotLights::OnLight(int32 InIndex, FLinearColor InColor)
{
	for (int32 i = 0; i < 3; i++)
	{
		SpotLightComp[i]->SetLightColor(FLinearColor::White);
	}

	SpotLightComp[InIndex]->SetLightColor(InColor);
}

