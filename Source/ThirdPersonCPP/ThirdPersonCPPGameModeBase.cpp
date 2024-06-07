#include "ThirdPersonCPPGameModeBase.h"
#include "CPlayer.h"

AThirdPersonCPPGameModeBase::AThirdPersonCPPGameModeBase()
{
	ConstructorHelpers::FClassFinder<APawn> pawnAsset(TEXT("Blueprint'/Game/BP_CPlayer.BP_CPlayer_C'"));

	if (pawnAsset.Succeeded())
	{
		DefaultPawnClass = pawnAsset.Class;
	}
	
	
}