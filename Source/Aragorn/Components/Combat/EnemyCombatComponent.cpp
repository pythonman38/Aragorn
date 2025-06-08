// Midnight Madness Inc. All Rights Reserved.


#include "EnemyCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Aragorn/Singletons/AragornDebugHelper.h"
#include "Aragorn/Singletons/AragornFunctionLibrary.h"
#include "Aragorn/Singletons/AragornGameplayTags.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor)) return;

	// TODO: Implement block check
	OverlappedActors.AddUnique(HitActor);

	bool bIsValidBlock = false;
	const bool bIsPlayerBlocking = UAragornFunctionLibrary::NativeDoesActorHaveTag(HitActor, AragornGameplayTags::Player_Status_Blocking),
		bIsMyAttackUnblockable = false;
	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		bIsValidBlock = UAragornFunctionLibrary::IsValidBlock(GetOwningPawn(), HitActor);
	}

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;

	if (bIsValidBlock) UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor, AragornGameplayTags::Player_Event_SuccessfulBlock, EventData);
	else UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), AragornGameplayTags::Shared_Event_MeleeHit, EventData);
}
