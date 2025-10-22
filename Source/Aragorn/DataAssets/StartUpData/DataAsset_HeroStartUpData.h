// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset_StartUpDataBase.h"
#include "Aragorn/Singletons/AragornStructTypes.h"
#include "DataAsset_HeroStartUpData.generated.h"

UCLASS()
class ARAGORN_API UDataAsset_HeroStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UAragornAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = StartUpData, meta = (TitleProperty = InputTag))
	TArray<FAragornHeroAbilitySet> HeroStartupAbilitySets;
};
