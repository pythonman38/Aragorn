// Midnight Madness Inc. All Rights Reserved.


#include "AragornBaseAnimInstance.h"

#include "Aragorn/Singletons/AragornFunctionLibrary.h"

bool UAragornBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if (auto OwningPawn = TryGetPawnOwner())
	{
		return UAragornFunctionLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
	}
	return false;
}
