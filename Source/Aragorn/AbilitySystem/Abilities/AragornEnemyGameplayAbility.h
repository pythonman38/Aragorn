// Midnight Madness, Inc.

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

private:
	TWeakObjectPtr<AAragornEnemyCharacter> CachedAragornEnemyCharacter;
};
