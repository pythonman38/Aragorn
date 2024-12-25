// Midnight Madness Inc. All Rights Reserved.


#include "AragornBaseCharacter.h"

#include "Aragorn/AbilitySystem/AragornAbilitySystemComponent.h"
#include "Aragorn/AbilitySystem/AragornAttributeSet.h"
#include "MotionWarpingComponent.h"

AAragornBaseCharacter::AAragornBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	AragornAbilitySystemComponent = CreateDefaultSubobject<UAragornAbilitySystemComponent>("AragornAbilitySystemComp");

	AragornAttributeSet = CreateDefaultSubobject<UAragornAttributeSet>("AragornAttributeSet");

	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
}

UAbilitySystemComponent* AAragornBaseCharacter::GetAbilitySystemComponent() const
{
	return GetAragornAbilitySystemComponent();
}

UPawnUIComponent* AAragornBaseCharacter::GetPawnUIComponent() const
{
	return nullptr;
}

UPawnCombatComponent* AAragornBaseCharacter::GetPawnCombatComponent() const
{
	return nullptr;
}

void AAragornBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AragornAbilitySystemComponent)
	{
		AragornAbilitySystemComponent->InitAbilityActorInfo(this, this);

		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot to assign Startup Data to %s!"), *GetName());
	}
}
