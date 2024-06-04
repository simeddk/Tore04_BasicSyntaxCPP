#pragma once

#include "CoreMinimal.h"
#include "CBall.generated.h"
#include "GameFramework/Actor.h"

UCLASS()
class THIRDPERSONCPP_API ACBall : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBall();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;
};
