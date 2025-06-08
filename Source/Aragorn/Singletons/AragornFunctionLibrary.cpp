// Midnight Madness Inc. All Rights Reserved.


#include "AragornFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Aragorn/AbilitySystem/AragornAbilitySystemComponent.h"
#include "Aragorn/Interfaces/PawnCombatInterface.h"
#include "GenericTeamAgentInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "Aragorn/Singletons/AragornDebugHelper.h"
#include "Aragorn/Singletons/AragornGameplayTags.h"

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

void UAragornFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
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

float UAragornFunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel)
{
	return InScalableFloat.GetValueAtLevel(InLevel);
}

FGameplayTag UAragornFunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference)
{
	check(InAttacker && InVictim);

	const FVector VictimForward = InVictim->GetActorForwardVector(),
		VictimToAttackerNormalized = (InAttacker->GetActorLocation() - InVictim->GetActorLocation()).GetSafeNormal();
	const float DotResult = FVector::DotProduct(VictimForward, VictimToAttackerNormalized);
	OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);

	const FVector CrossResult = FVector::CrossProduct(VictimForward, VictimToAttackerNormalized);

	if (CrossResult.Z < 0.f) OutAngleDifference *= -1.f;
	if (OutAngleDifference >= -45.f && OutAngleDifference <= 45.f) return AragornGameplayTags::Shared_Status_HitReact_Front;
	else if (OutAngleDifference < -45.f && OutAngleDifference > -135.f) return AragornGameplayTags::Shared_Status_HitReact_Left;
	else if (OutAngleDifference < -135.f || OutAngleDifference > 135.f) return AragornGameplayTags::Shared_Status_HitReact_Back;
	else if (OutAngleDifference > 45.f && OutAngleDifference <= 135.f) return AragornGameplayTags::Shared_Status_HitReact_Right;

	return AragornGameplayTags::Shared_Status_HitReact_Front;
}

bool UAragornFunctionLibrary::IsValidBlock(AActor* InAttacker, AActor* InDefender)
{
	check(InAttacker && InDefender);

	const float DotResult = FVector::DotProduct(InAttacker->GetActorForwardVector(), InDefender->GetActorForwardVector());

	return DotResult < -0.1f;
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
