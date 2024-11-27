// Midnight Madness Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Aragorn/AbilitySystem/AragornAbilitySystemComponent.h"
#include "AragornAttributeSet.generated.h"

class IPawnUI_Interface;

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class ARAGORN_API UAragornAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UAragornAttributeSet();

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, Category = Health)
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UAragornAttributeSet, CurrentHealth)

	UPROPERTY(BlueprintReadOnly, Category = Health)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAragornAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = Rage)
	FGameplayAttributeData CurrentRage;
	ATTRIBUTE_ACCESSORS(UAragornAttributeSet, CurrentRage)

	UPROPERTY(BlueprintReadOnly, Category = Rage)
	FGameplayAttributeData MaxRage;
	ATTRIBUTE_ACCESSORS(UAragornAttributeSet, MaxRage)

	UPROPERTY(BlueprintReadOnly, Category = Damage)
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UAragornAttributeSet, AttackPower)

	UPROPERTY(BlueprintReadOnly, Category = Damage)
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UAragornAttributeSet, DefensePower)

	UPROPERTY(BlueprintReadOnly, Category = Damage)
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(UAragornAttributeSet, DamageTaken)

private:
	TWeakInterfacePtr<IPawnUI_Interface> CachedPawnUI_Interface;
};
