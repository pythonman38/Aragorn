// Midnight Madness Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AragornBaseCharacter.h"
#include "GameplayTagContainer.h"
#include "AragornHeroCharacter.generated.h"

class UCameraComponent;
class UDataAsset_InputConfig;
class UHeroCombatComponent;
class UHeroUIComponent;
class USpringArmComponent;

struct FInputActionValue;

UCLASS()
class ARAGORN_API AAragornHeroCharacter : public AAragornBaseCharacter
{
	GENERATED_BODY()

public:
	AAragornHeroCharacter();

	// Inherited via IPawnCombatInterface
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;

	// Inherited via IPawn UI Interface
	virtual UPawnUIComponent* GetPawnUIComponent() const override;

	virtual UHeroUIComponent* GetHeroUIComponent() const override;

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Interited via APawn Interface
	virtual void PossessedBy(AController* NewController) override;

	void Input_Move(const FInputActionValue& InputActionValue);

	void Input_Look(const FInputActionValue& InputActionValue);

	void Input_AbilityInputPressed(FGameplayTag InInputTag);

	void Input_AbilityInputReleased(FGameplayTag InInputTag);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = true))
	TObjectPtr<UHeroCombatComponent> HeroCompbatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HUD, meta = (AllowPrivateAccess = true))
	TObjectPtr<UHeroUIComponent> HeroUIComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = CharacterData, meta = (AllowPrivateAccess = true))
	TObjectPtr<UDataAsset_InputConfig> InputConfigDataAsset;

public:
	// Getters for private variables
	FORCEINLINE UHeroCombatComponent* GetHeroCombatComponent() const { return HeroCompbatComponent; }
};
