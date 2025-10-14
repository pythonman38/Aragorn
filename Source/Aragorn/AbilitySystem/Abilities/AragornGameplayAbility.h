// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AragornGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class EAragornAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

UCLASS()
class ARAGORN_API UAragornGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UAragornGameplayAbility();

protected:
	// UGameplayAbility Interface
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = AragornAbility)
	EAragornAbilityActivationPolicy AbilityActivationPolicy;
};
