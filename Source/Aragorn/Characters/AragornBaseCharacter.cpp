// Midnight Madness, Inc.


#include "AragornBaseCharacter.h"

#include "Aragorn/AbilitySystem/AragornAbilitySystemComponent.h"
#include "Aragorn/AbilitySystem/AragornAttributeSet.h"

AAragornBaseCharacter::AAragornBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	GetMesh()->bReceivesDecals = false;

	AragornAbilitySystemComponent = CreateDefaultSubobject<UAragornAbilitySystemComponent>("AragornAbilitySystemComp");
	AragornAttributeSet = CreateDefaultSubobject<UAragornAttributeSet>("AragornAttributeSet");
}

void AAragornBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AragornAbilitySystemComponent)
	{
		AragornAbilitySystemComponent->InitAbilityActorInfo(this, this);

		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());
	}
}

UAbilitySystemComponent* AAragornBaseCharacter::GetAbilitySystemComponent() const
{
	return GetAragornAbilitySystemComponent();
}

UPawnCombatComponent* AAragornBaseCharacter::GetPawnCombatComponent() const
{
	return nullptr;
}

UPawnUI_Component* AAragornBaseCharacter::GetPawnUI_Component() const
{
	return nullptr;
}



