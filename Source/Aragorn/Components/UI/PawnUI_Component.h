// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "../PawnExtensionComponentBase.h"
#include "PawnUI_Component.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPercentChangedDelegate, float, NewPercent);

UCLASS()
class ARAGORN_API UPawnUI_Component : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangedDelegate OnCurrentHealthChanged;
};
