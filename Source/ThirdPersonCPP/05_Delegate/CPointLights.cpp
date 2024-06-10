#include "CPointLights.h"
#include "Global.h"
#include "Components/PointLightComponent.h"
#include "CBoxBase_Delegate.h"

ACPointLights::ACPointLights()
{
	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	RootComponent = RootComp;

	PointLightComp1 = CreateDefaultSubobject<UPointLightComponent>("PointLightComp1");
	PointLightComp1->SetupAttachment(RootComp);

	PointLightComp2 = CreateDefaultSubobject<UPointLightComponent>("PointLightComp2");
	PointLightComp2->SetupAttachment(RootComp);

	PointLightComp1->Intensity = 1e+4f;
	PointLightComp1->AttenuationRadius = 200.f;
	PointLightComp1->LightColor = FColor(255, 128, 50);

	PointLightComp2->SetRelativeLocation(FVector(0, 200, 0));
	PointLightComp2->Intensity = 1e+4f;
	PointLightComp2->AttenuationRadius = 200.f;
	PointLightComp2->LightColor = FColor(255, 128, 50);
}

void ACPointLights::BeginPlay()
{
	Super::BeginPlay();
	
	PointLightComp1->SetVisibility(false);
	PointLightComp2->SetVisibility(false);

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACBoxBase_Delegate::StaticClass(), actors);

	if (actors.Num() > 0)
	{
		ACBoxBase_Delegate* trigger = Cast<ACBoxBase_Delegate>(actors[0]);
		if (trigger)
		{
			trigger->OnBoxBeginOverlap.BindUFunction(this, "OnLights");
			trigger->OnBoxEndOverlap.BindUFunction(this, "OffLights");

			trigger->OnBoxOneParam.BindUFunction(this, "OnRandomLight");
		}
	}
}

void ACPointLights::OnLights()
{
	PointLightComp1->SetVisibility(true);
	//PointLightComp2->SetVisibility(true);
}

void ACPointLights::OffLights()
{
	PointLightComp1->SetVisibility(false);
	PointLightComp2->SetVisibility(false);
}

FString ACPointLights::OnRandomLight(FLinearColor InColor)
{
	PointLightComp2->SetVisibility(true);
	PointLightComp2->SetLightColor(InColor);

	//return InColor.ToString();
	FString ReturnStr = FString::Printf(TEXT("RandomColor is %s"), *InColor.ToString());
	return ReturnStr;
}

