// Midnight Madness, Inc.


#include "DataAsset_HeroStartUpData.h"

#include "Aragorn/AbilitySystem/AragornAbilitySystemComponent.h"
#include "Aragorn/AbilitySystem/Abilities/AragornHeroGameplayAbility.h"



void UDataAsset_HeroStartUpData::GiveToAbilitySystemComponent(UAragornAbilitySystemComponent* InASCToGive,
	int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	for (const auto& AbilitySet : HeroStartupAbilitySets)
	{
		if (!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);
		InASCToGive->GiveAbility(AbilitySpec);
	}
}
