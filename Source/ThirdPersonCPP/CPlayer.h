#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ACBoxBase_Chest;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGotKey);

UCLASS()
class THIRDPERSONCPP_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ACPlayer();

	const TArray<FName>& GetHasKeys();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);

	void OnSprint();
	void OffSprint();

	void OnInteract();

private:
	UFUNCTION()
	void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void EndOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	UPROPERTY(BlueprintAssignable)
	FOnGotKey OnGotKey;

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

protected:
	UPROPERTY(BlueprintReadOnly)
	TArray<FName> HasKeys;

private:
	ACBoxBase_Chest* InteractableActor;
};
