// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset_StartUpDataBase.h"
#include "DataAsset_EnemyStartUpData.generated.h"


class UAragornEnemyGameplayAbility;

UCLASS()
class ARAGORN_API UDataAsset_EnemyStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UAragornAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = StartUpData)
	TArray<TSubclassOf<UAragornEnemyGameplayAbility>> EnemyCombatAbilities;
};
