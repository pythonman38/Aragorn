// Midnight Madness Inc. All Rights Reserved.


#include "AragornFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Aragorn/AbilitySystem/AragornAbilitySystemComponent.h"

UAragornAbilitySystemComponent* UAragornFunctionLibrary::NativeGetAragornASCFromActor(AActor* InActor)
{
	check(InActor);

	return CastChecked<UAragornAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UAragornFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UAragornAbilitySystemComponent* ASC = NativeGetAragornASCFromActor(InActor);

	if (!ASC->HasMatchingGameplayTag(TagToAdd)) ASC->AddLooseGameplayTag(TagToAdd);
}

void UAragornFunctionLibrary::RemoveGameplayFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	UAragornAbilitySystemComponent* ASC = NativeGetAragornASCFromActor(InActor);

	if (ASC->HasMatchingGameplayTag(TagToRemove)) ASC->RemoveLooseGameplayTag(TagToRemove);
}

void UAragornFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EAragornConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? EAragornConfirmType::Yes : EAragornConfirmType::No;
}

bool UAragornFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UAragornAbilitySystemComponent* ASC = NativeGetAragornASCFromActor(InActor);

	return ASC->HasMatchingGameplayTag(TagToCheck);
}
