#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBoxBase.generated.h"

class UBoxComponent;
class UTextRenderComponent;

UCLASS()
class THIRDPERSONCPP_API ACBoxBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBoxBase();

protected:
	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	virtual void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	virtual void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere)
	UTextRenderComponent* TextRenderComp;

};
