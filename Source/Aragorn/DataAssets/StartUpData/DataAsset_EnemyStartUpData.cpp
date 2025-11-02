// Midnight Madness, Inc.


#include "DataAsset_EnemyStartUpData.h"

#include "Aragorn/AbilitySystem/AragornAbilitySystemComponent.h"
#include "Aragorn/AbilitySystem/Abilities/AragornEnemyGameplayAbility.h"

void UDataAsset_EnemyStartUpData::GiveToAbilitySystemComponent(UAragornAbilitySystemComponent* InASCToGive,
                                                               int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	if (!EnemyCombatAbilities.IsEmpty())
	{
		for (const auto& AbilityClass : EnemyCombatAbilities)
		{
			if (!AbilityClass) continue;
			FGameplayAbilitySpec AbilitySpec(AbilityClass);
			AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
			AbilitySpec.Level = ApplyLevel;
			InASCToGive->GiveAbility(AbilitySpec);
		}
	}
}
