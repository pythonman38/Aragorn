// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "../PawnExtensionComponentBase.h"
#include "PawnCombatComponent.generated.h"


class AAragornWeaponBase;

UCLASS()
class ARAGORN_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Aragorn|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AAragornWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon = false);

	UFUNCTION(BlueprintCallable, Category = "Aragorn|Combat")
	AAragornWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	UFUNCTION(BlueprintCallable, Category = "Aragorn|Combat")
	AAragornWeaponBase* GetCharacterCurrentEquippedWeapon() const;

public:
	UPROPERTY(BlueprintReadWrite, Category = "Aragorn|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

private:
	TMap<FGameplayTag, AAragornWeaponBase*> CharacterCarriedWeaponMap;
};
