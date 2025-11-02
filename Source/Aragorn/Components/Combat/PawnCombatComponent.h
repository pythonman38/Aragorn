// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "../PawnExtensionComponentBase.h"
#include "PawnCombatComponent.generated.h"

UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
	CurrentEquippedWeapon,
	LeftHand,
	RightHand
};

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

	UFUNCTION(BlueprintCallable, Category = "Aragorn|Combat")
	void ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon);

	virtual void OnHitTargetActor(AActor* HitActor);

	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor);

public:
	UPROPERTY(BlueprintReadWrite, Category = "Aragorn|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

protected:
	TArray<AActor*> OverlappedActors;

private:
	TMap<FGameplayTag, AAragornWeaponBase*> CharacterCarriedWeaponMap;
};
