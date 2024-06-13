#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CWeaponInterface.generated.h"

class ACWeapon;

UINTERFACE(MinimalAPI)
class UCWeaponInterface : public UInterface
{
	GENERATED_BODY()
};

class THIRDPERSONCPP_API ICWeaponInterface
{
	GENERATED_BODY()

public:
	virtual ACWeapon* GetWeapon() = 0;
};
