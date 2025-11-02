// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Aragorn/Interfaces/PawnCombatInterface.h"
#include "Aragorn/Interfaces/PawnUI_Interface.h"
#include "AragornBaseCharacter.generated.h"

class UAragornAbilitySystemComponent;
class UAragornAttributeSet;
class UDataAsset_StartUpDataBase;

UCLASS()
class ARAGORN_API AAragornBaseCharacter : public ACharacter, public IAbilitySystemInterface, public IPawnCombatInterface, public IPawnUI_Interface
{
	GENERATED_BODY()

public:
	AAragornBaseCharacter();

	// IAbilitySystemInterface Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// IPawnCombatInterface Interface
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;

	// IPawnUI_Interface Interface
	virtual UPawnUI_Component* GetPawnUI_Component() const override;

protected:
	// APawn Interface
	virtual void PossessedBy(AController* NewController) override;

	

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AbilitySystem)
	TObjectPtr<UAragornAbilitySystemComponent> AragornAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AbilitySystem)
	TObjectPtr<UAragornAttributeSet> AragornAttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = CharacterData)
	TSoftObjectPtr<UDataAsset_StartUpDataBase> CharacterStartUpData;

public:
	// Getters for private variables
	FORCEINLINE UAragornAbilitySystemComponent* GetAragornAbilitySystemComponent() const { return AragornAbilitySystemComponent; }
	FORCEINLINE UAragornAttributeSet* GetAragornAttributeSet() const { return AragornAttributeSet; }
};
