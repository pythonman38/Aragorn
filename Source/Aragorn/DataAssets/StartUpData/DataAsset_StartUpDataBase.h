// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"


class UAragornAbilitySystemComponent;
class UAragornGameplayAbility;

UCLASS()
class ARAGORN_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UAragornAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

protected:
	UPROPERTY(EditDefaultsOnly, Category = StartUpData)
	TArray<TSubclassOf<UAragornGameplayAbility>> ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = StartUpData)
	TArray<TSubclassOf<UAragornGameplayAbility>> ReactiveAbilities;

protected:
	void GrantAbilities(const TArray<TSubclassOf<UAragornGameplayAbility>>& InAbilitiesToGive,
		UAragornAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
};
