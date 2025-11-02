// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "PawnUI_Component.h"
#include "HeroUI_Component.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquippedWeaponChangedDelegate, TSoftObjectPtr<UTexture2D>, SoftWeaponIcon);

UCLASS()
class ARAGORN_API UHeroUI_Component : public UPawnUI_Component
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangedDelegate OnCurrentRageChanged;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnEquippedWeaponChangedDelegate OnEquippedWeaponChanged;
	
};
