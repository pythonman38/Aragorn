// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Aragorn/DataAssets/Input/DataAsset_InputConfig.h"
#include "Templates/IsMemberPointer.h"
#include "AragornInputComponent.generated.h"


UCLASS()
class ARAGORN_API UAragornInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag,
	                           ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
	{
		checkf(InInputConfig, TEXT("Input config data asset is null, cannot proceed with binding!"));

		if (auto FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
		{
			if constexpr (TIsMemberPointer<CallbackFunc>::Value) BindAction(FoundAction, TriggerEvent, ContextObject, Func);
		}
	}
};
