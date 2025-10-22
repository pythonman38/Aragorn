// Midnight Madness, Inc.


#include "AragornFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Aragorn/AbilitySystem/AragornAbilitySystemComponent.h"

UAragornAbilitySystemComponent* UAragornFunctionLibrary::NativeGetAragornASCFromActor(AActor* InActor)
{
	check(InActor);

	return CastChecked<UAragornAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

bool UAragornFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	auto ASC = NativeGetAragornASCFromActor(InActor);
	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UAragornFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	auto ASC = NativeGetAragornASCFromActor(InActor);
	if (!ASC->HasMatchingGameplayTag(TagToAdd)) ASC->AddLooseGameplayTag(TagToAdd);
}

void UAragornFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	auto ASC = NativeGetAragornASCFromActor(InActor);
	if (ASC->HasMatchingGameplayTag(TagToRemove)) ASC->RemoveLooseGameplayTag(TagToRemove);
}

void UAragornFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck,
	EAragornConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? EAragornConfirmType::Yes : EAragornConfirmType::No;
}
