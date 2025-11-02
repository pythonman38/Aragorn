// Midnight Madness, Inc.


#include "AragornHeroGameplayAbility.h"

#include "Aragorn/AbilitySystem/AragornAbilitySystemComponent.h"
#include "Aragorn/Characters/AragornHeroCharacter.h"
#include "Aragorn/Controllers/AragornHeroController.h"
#include "Aragorn/Singletons/AragornGameplayTags.h"

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

FGameplayEffectSpecHandle UAragornHeroGameplayAbility::MakeHeroDamageEffectSpecHandle(
	TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag,
	int32 InUsedComboCount)
{
	check(EffectClass);

	auto ContextHandle = GetAragornAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetHeroCharacterFromActorInfo(), GetAvatarActorFromActorInfo());
	auto EffectSpecHandle = GetAragornAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(EffectClass, GetAbilityLevel(), ContextHandle);
	EffectSpecHandle.Data->SetSetByCallerMagnitude(AragornGameplayTags::Shared_SetByCaller_BaseDamage, InWeaponBaseDamage);
	if (InCurrentAttackTypeTag.IsValid()) EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InUsedComboCount);
	return EffectSpecHandle;
}
