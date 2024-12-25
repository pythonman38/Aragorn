// Midnight Madness Inc. All Rights Reserved.


#include "EnemyCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Aragorn/Singletons/AragornDebugHelper.h"
#include "Aragorn/Singletons/AragornGameplayTags.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor)) return;

	// TODO: Implement block check
	OverlappedActors.AddUnique(HitActor);

	bool bIsValidBlock = false;
	const bool bIsPlayerBlocking = false, bIsMyAttackUnblockable = false;
	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		//TODO: Check if the block is valid
	}

	if (bIsValidBlock)
	{
		//TODO: Handle successful block
	}
	else
	{
		FGameplayEventData EventData;
		EventData.Instigator = GetOwningPawn();
		EventData.Target = HitActor;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), AragornGameplayTags::Shared_Event_MeleeHit, EventData);
	}
}
