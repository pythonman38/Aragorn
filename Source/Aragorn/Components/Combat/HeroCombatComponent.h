// Midnight Madness Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PawnCombatComponent.h"
#include "HeroCombatComponent.generated.h"

class AAragornHeroWeapon;

UCLASS()
class ARAGORN_API UHeroCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	AAragornHeroWeapon* GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const;
};