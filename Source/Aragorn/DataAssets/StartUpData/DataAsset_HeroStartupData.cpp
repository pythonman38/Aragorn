// Midnight Madness Inc. All Rights Reserved.


#include "DataAsset_HeroStartupData.h"

#include "Aragorn/Abilities/AragornHeroGameplayAbility.h"
#include "Aragorn/AbilitySystem/AragornAbilitySystemComponent.h"

void UDataAsset_HeroStartupData::GiveToAbilitySystemComponent(UAragornAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	for (const FAragornHeroAbilitySet& AbilitySet : HeroStartupAbilitySets)
	{
		if (!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

		InASCToGive->GiveAbility(AbilitySpec);
	}
}
