// Midnight Madness, Inc.


#include "AragornHeroGameplayAbility.h"

#include "Aragorn/Characters/AragornHeroCharacter.h"
#include "Aragorn/Controllers/AragornHeroController.h"

AAragornHeroCharacter* UAragornHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
	if (!CachedAragornHeroCharacter.IsValid())
	{
		CachedAragornHeroCharacter = Cast<AAragornHeroCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedAragornHeroCharacter.IsValid() ? CachedAragornHeroCharacter.Get() : nullptr;
}

AAragornHeroController* UAragornHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
	if (!CachedAragornHeroController.IsValid())
	{
		CachedAragornHeroController = Cast<AAragornHeroController>(CurrentActorInfo->PlayerController);
	}
	return CachedAragornHeroController.IsValid() ? CachedAragornHeroController.Get() : nullptr;
}

UHeroCombatComponent* UAragornHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
	return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}
