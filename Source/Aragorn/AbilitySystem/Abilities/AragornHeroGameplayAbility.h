// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "AragornGameplayAbility.h"
#include "AragornHeroGameplayAbility.generated.h"


class UHeroCombatComponent;
class AAragornHeroController;
class AAragornHeroCharacter;

UCLASS()
class ARAGORN_API UAragornHeroGameplayAbility : public UAragornGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Aragorn|Ability")
	AAragornHeroCharacter* GetHeroCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Aragorn|Ability")
	AAragornHeroController* GetHeroControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Aragorn|Ability")
	UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();

private:
	TWeakObjectPtr<AAragornHeroCharacter> CachedAragornHeroCharacter;
	TWeakObjectPtr<AAragornHeroController> CachedAragornHeroController;
};
