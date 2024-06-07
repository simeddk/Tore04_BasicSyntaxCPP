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
	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere)
	UTextRenderComponent* TextRenderComp;

};
