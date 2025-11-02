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
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_HitPause);

	/** Player Weapon Tags **/
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe);

	/** Player Event Tags **/
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe);
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Axe);
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_HitPause);

	/** Player Status Tags **/
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher);

	/** Player SetByCaller Tags **/
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Light);
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Heavy);

	/** Enemy Weapon Tags **/
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon);

	/** Enemy Ability Tags **/
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee);
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Ranged);

	/** Shared Ability Tags **/
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_HitReact);
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_Death);

	/** Shared Event Tags **/
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_MeleeHit);
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_HitReact);

	/** Shared SetByCaller Tags **/
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_BaseDamage);

	/** Shared Status Tags **/
	ARAGORN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Dead);
}
