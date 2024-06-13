#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CWeaponInterface.h"
#include "CPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UMaterialInstanceDynamic;
class ACWeapon;

UCLASS()
class THIRDPERSONCPP_API ACPlayer : public ACharacter, public ICWeaponInterface
{
	GENERATED_BODY()

public:
	ACPlayer();

	UFUNCTION(Exec)
	void ChangeSpeed(float InMoveSpeed = 400.f);

	FORCEINLINE ACWeapon* GetWeapon() override { return Weapon; }

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);

	void OnSprint();
	void OffSprint();

	void ToggleEquip();

public:
	UFUNCTION(BlueprintCallable)
	void SetBodyColor(FLinearColor InBodyColor, FLinearColor InLogoColor);

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

private:
	UMaterialInstanceDynamic* BodyMaterial;
	UMaterialInstanceDynamic* LogoMaterial;

	ACWeapon* Weapon;
};
