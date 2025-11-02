// Midnight Madness, Inc.


#include "HeroCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Aragorn/Items/Weapons/AragornHeroWeapon.h"
#include "Aragorn/Singletons/AragornGameplayTags.h"

AAragornHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AAragornHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

AAragornHeroWeapon* UHeroCombatComponent::GetHeroCurrentEquippedWeapon() const
{
	return Cast<AAragornHeroWeapon>(GetCharacterCurrentEquippedWeapon());
}

float UHeroCombatComponent::GetHeroCurrentEquippedWeaponDamageAtLevel(float InLevel) const
{
	return GetHeroCurrentEquippedWeapon()->HeroWeaponData.WeaponBaseDamage.GetValueAtLevel((InLevel));
}

void UHeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor)) return;

	OverlappedActors.AddUnique(HitActor);
	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), AragornGameplayTags::Shared_Event_MeleeHit, Data);
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), AragornGameplayTags::Player_Event_HitPause, FGameplayEventData());
}

void UHeroCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), AragornGameplayTags::Player_Event_HitPause, FGameplayEventData());
}
