// Midnight Madness Inc. All Rights Reserved.


#include "HeroCombatComponent.h"

#include "Aragorn/Items/Weapons/AragornHeroWeapon.h"

AAragornHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AAragornHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}