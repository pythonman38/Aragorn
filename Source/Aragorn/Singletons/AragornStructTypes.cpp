// Midnight Madness, Inc.


#include "AragornStructTypes.h"

#include "Aragorn/AbilitySystem/Abilities/AragornHeroGameplayAbility.h"


bool FAragornHeroAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
