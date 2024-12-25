// Midnight Madness Inc. All Rights Reserved.


#include "AragornEnemyGameplayAbility.h"

#include "Aragorn/AbilitySystem/AragornAbilitySystemComponent.h"
#include "Aragorn/Characters/AragornEnemyCharacter.h"
#include "Aragorn/Singletons/AragornGameplayTags.h"

AAragornEnemyCharacter* UAragornEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedAragornEnemyCharacter.IsValid())
	{
		CachedAragornEnemyCharacter = Cast<AAragornEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedAragornEnemyCharacter.IsValid() ? CachedAragornEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UAragornEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}

FGameplayEffectSpecHandle UAragornEnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat)
{
	check(EffectClass);

	auto ContextHandle = GetAragornAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());
	auto EffectSpecHandle = GetAragornAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(EffectClass, GetAbilityLevel(), ContextHandle);
	EffectSpecHandle.Data->SetSetByCallerMagnitude(AragornGameplayTags::Shared_SetByCaller_BaseDamage, InDamageScalableFloat.GetValueAtLevel(GetAbilityLevel()));

	return EffectSpecHandle;
}
