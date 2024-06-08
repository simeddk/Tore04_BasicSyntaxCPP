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

	//@ A getter that returns the HasKeys below to the outside.
	const TArray<FName>& GetHasKeys();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);

	void OnSprint();
	void OffSprint();

	//@ 'F' Key Action Event, Binding by SetupPlayerInputComponent fuction.
	void OnInteract();

	//@ Capsule Collision Event
private:
	UFUNCTION()
	void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void EndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	//@ I want to do something when the actual interaction occurs. Here, we want to display the status of keys currently owned by the player using a widget.
public:
	UPROPERTY(BlueprintAssignable)
	FOnGotKey OnGotKey;

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	//@ List of keys obtained by opening boxes.
protected:
	UPROPERTY(BlueprintReadOnly)
	TArray<FName> HasKeys;

	//@ BoxBased Actor overlapping with capsule collision
private:
	ACBoxBase_Chest* InteractableActor;
};
