// Midnight Madness Inc. All Rights Reserved.


#include "AragornHeroController.h"

AAragornHeroController::AAragornHeroController()
{
	HeroTeamId = FGenericTeamId(0);
}

FGenericTeamId AAragornHeroController::GetGenericTeamId() const
{
	return HeroTeamId;
}
