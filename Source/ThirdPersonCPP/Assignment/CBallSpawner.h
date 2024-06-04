#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBallSpawner.generated.h"

class ACBall;

UCLASS()
class THIRDPERSONCPP_API ACBallSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBallSpawner();

protected:
	UFUNCTION(BlueprintCallable)
	void SpawnBall();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	FVector2D SpawnOffset;

private:
	TSubclassOf<ACBall> BallClass;
};
