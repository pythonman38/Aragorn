// Midnight Madness Inc. All Rights Reserved.

#include "AragornStructTypes.h"

#include "Aragorn/Abilities/AragornHeroGameplayAbility.h"

bool FAragornHeroAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
