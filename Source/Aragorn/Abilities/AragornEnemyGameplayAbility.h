// Midnight Madness Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AragornGameplayAbility.h"
#include "AragornEnemyGameplayAbility.generated.h"

class AAragornEnemyCharacter;
class UEnemyCombatComponent;

UCLASS()
class ARAGORN_API UAragornEnemyGameplayAbility : public UAragornGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Aragorn|Ability")
	AAragornEnemyCharacter* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Aragorn|Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Aragorn|Ability")
	FGameplayEffectSpecHandle MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat);

private:
	TWeakObjectPtr<AAragornEnemyCharacter> CachedAragornEnemyCharacter;
};
