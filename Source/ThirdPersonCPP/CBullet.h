#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBullet.generated.h"

class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class THIRDPERSONCPP_API ACBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBullet();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleDefaultsOnly)
	UProjectileMovementComponent* ProjectileComp;

};
