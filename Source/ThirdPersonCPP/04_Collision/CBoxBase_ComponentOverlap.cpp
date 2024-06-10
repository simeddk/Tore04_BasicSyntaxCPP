#include "CBoxBase_ComponentOverlap.h"
#include "Components/PointLightComponent.h"
#include "Components/BoxComponent.h"

ACBoxBase_ComponentOverlap::ACBoxBase_ComponentOverlap()
{
	PointLightComp = CreateDefaultSubobject<UPointLightComponent>("PointLightComp");
	PointLightComp->SetupAttachment(RootComp);
	PointLightComp->SetLightColor(FLinearColor::Green);
}

void ACBoxBase_ComponentOverlap::BeginPlay()
{
	Super::BeginPlay();

	PointLightComp->SetVisibility(false);

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ACBoxBase_ComponentOverlap::ComponentBeginOverlap);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &ACBoxBase_ComponentOverlap::ComponentEndOverlap);
}

void ACBoxBase_ComponentOverlap::ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PointLightComp->SetVisibility(true);
}

void ACBoxBase_ComponentOverlap::ComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PointLightComp->SetVisibility(false);
}
