// Midnight Madness Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AragornBaseCharacter.generated.h"

class UAragornAbilitySystemComponent;
class UAragornAttributeSet;
class UDataAsset_StartUpDataBase;

UCLASS()
class ARAGORN_API AAragornBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAragornBaseCharacter();

	// Inherited via IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	// Interited via APawn Interface
	virtual void PossessedBy(AController* NewController) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AbilitySystem)
	TObjectPtr<UAragornAbilitySystemComponent> AragornAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AbilitySystem)
	TObjectPtr<UAragornAttributeSet> AragornAttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = CharacterData)
	TSoftObjectPtr<UDataAsset_StartUpDataBase> CharacterStartUpData;

public:
	// Getters for protected variables
	FORCEINLINE UAragornAbilitySystemComponent* GetAragornAbilitySystemComponent() const { return AragornAbilitySystemComponent; }
	FORCEINLINE UAragornAttributeSet* GetAragornAttributeSet() const { return AragornAttributeSet; }
};
