// Midnight Madness, Inc.


#include "DataAsset_InputConfig.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const auto& Action : NativeInputActions)
	{
		if (Action.InputTag == InInputTag && Action.InputAction) return Action.InputAction;
	}
	return nullptr;
}
