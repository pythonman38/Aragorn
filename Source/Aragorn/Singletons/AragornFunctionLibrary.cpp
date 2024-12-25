// Midnight Madness Inc. All Rights Reserved.


#include "AragornFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Aragorn/AbilitySystem/AragornAbilitySystemComponent.h"
#include "Aragorn/Interfaces/PawnCombatInterface.h"
#include "GenericTeamAgentInterface.h"

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

UPawnCombatComponent* UAragornFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor, EAragornValidType& OutValidType)
{
	auto CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);

	OutValidType = CombatComponent ? EAragornValidType::Valid : EAragornValidType::Invalid;

	return CombatComponent;
}

bool UAragornFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);
	auto QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	auto TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());
	if (QueryTeamAgent && TargetTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}
	return false;
}

UPawnCombatComponent* UAragornFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);
	if (auto PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}
	return nullptr;
}

bool UAragornFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UAragornAbilitySystemComponent* ASC = NativeGetAragornASCFromActor(InActor);

	return ASC->HasMatchingGameplayTag(TagToCheck);
}
