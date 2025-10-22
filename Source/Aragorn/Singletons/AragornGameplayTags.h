// Midnight Madness, Inc.

#pragma once

#include "NativeGameplayTags.h"

namespace AragornGameplayTags
{
	/** Player Input Tags **/
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EquipAxe);
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnequipAxe);
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LightAttack_Axe);
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HeavyAttack_Axe);

	/** Player Ability Tags **/
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Axe);
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Axe);
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Axe);
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Axe);

	/** Player Weapon Tags **/
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe);

	/** Player Event Tags **/
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe);
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Axe);

	/** Player Status Tags **/
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher);
}
