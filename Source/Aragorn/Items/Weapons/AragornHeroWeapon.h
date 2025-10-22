// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "AragornWeaponBase.h"
#include "GameplayAbilitySpecHandle.h"
#include "Aragorn/Singletons/AragornStructTypes.h"
#include "AragornHeroWeapon.generated.h"


UCLASS()
class ARAGORN_API AAragornHeroWeapon : public AAragornWeaponBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = WeaponData)
	FAragornHeroWeaponData HeroWeaponData;

	UFUNCTION(BlueprintCallable)
	void AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);

	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;

private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};
