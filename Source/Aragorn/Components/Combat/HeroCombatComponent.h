// Midnight Madness, Inc.

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
	

public:
	UFUNCTION(BlueprintCallable, Category = "Aragorn|Combat")
	AAragornHeroWeapon* GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const;

	UFUNCTION(BlueprintCallable, Category = "Aragorn|Combat")
	AAragornHeroWeapon* GetHeroCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "Aragorn|Combat")
	float GetHeroCurrentEquippedWeaponDamageAtLevel(float InLevel) const;

	virtual void OnHitTargetActor(AActor* HitActor) override;

	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor) override;
};
