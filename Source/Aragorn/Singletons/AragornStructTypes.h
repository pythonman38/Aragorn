// Midnight Madness Inc. All Rights Reserved.

#pragma once

#include "GameplayTagContainer.h"
#include "ScalableFloat.h"
#include "AragornStructTypes.generated.h"

class UAragornHeroGameplayAbility;
class UAragornHeroLinkedAnimLayer;
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FAragornHeroAbilitySet
{
	GENERATED_BODY()

	bool IsValid() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = InputTag))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UAragornHeroGameplayAbility> AbilityToGrant;
};

USTRUCT(BlueprintType)
struct FAragornHeroWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UAragornHeroLinkedAnimLayer> WeaponAnimLayerToLink;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> WeaponInputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = InputTag))
	TArray<FAragornHeroAbilitySet> DefaultWeaponAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat WeaponBaseDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> SoftWeaponIconTexture;
};