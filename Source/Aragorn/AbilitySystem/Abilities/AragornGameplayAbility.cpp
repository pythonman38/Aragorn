// Midnight Madness, Inc.


#include "AragornGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Aragorn/AbilitySystem/AragornAbilitySystemComponent.h"
#include "Aragorn/Components/Combat/PawnCombatComponent.h"

UAragornGameplayAbility::UAragornGameplayAbility() :
AbilityActivationPolicy(EAragornAbilityActivationPolicy::OnTriggered)
{
}

void UAragornGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (AbilityActivationPolicy == EAragornAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive()) ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
	}
}

void UAragornGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AbilityActivationPolicy == EAragornAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo) ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
	}
}

UPawnCombatComponent* UAragornGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

UAragornAbilitySystemComponent* UAragornGameplayAbility::GetAragornAbilitySystemComponentFromActorInfo() const
{
	return Cast<UAragornAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

FActiveGameplayEffectHandle UAragornGameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor,
	const FGameplayEffectSpecHandle& InSpecHandle) const
{
	auto TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	check(TargetASC && InSpecHandle.IsValid());
	return GetAragornAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);
}

FActiveGameplayEffectHandle UAragornGameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor,
	const FGameplayEffectSpecHandle& InSpecHandle, EAragornSuccessType& OutSuccessType)
{
	auto ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(TargetActor, InSpecHandle);
	OutSuccessType = ActiveGameplayEffectHandle.WasSuccessfullyApplied() ? EAragornSuccessType::Successful : EAragornSuccessType::Failed;
	return ActiveGameplayEffectHandle;
}
