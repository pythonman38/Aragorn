// Midnight Madness, Inc.


#include "AragornGameplayAbility.h"

#include "Aragorn/AbilitySystem/AragornAbilitySystemComponent.h"

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
