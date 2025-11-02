// Midnight Madness, Inc.


#include "AragornEnemyGameplayAbility.h"

#include "Aragorn/Characters/AragornEnemyCharacter.h"

AAragornEnemyCharacter* UAragornEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedAragornEnemyCharacter.IsValid())
	{
		CachedAragornEnemyCharacter = Cast<AAragornEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedAragornEnemyCharacter.IsValid() ? CachedAragornEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UAragornEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}
