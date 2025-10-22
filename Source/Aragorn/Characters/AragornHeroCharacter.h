// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "AragornBaseCharacter.h"
#include "GameplayTagContainer.h"
#include "AragornHeroCharacter.generated.h"

class UCameraComponent;
class UDataAsset_InputConfig;
class UHeroCombatComponent;
class USpringArmComponent;

struct FInputActionValue;

UCLASS()
class ARAGORN_API AAragornHeroCharacter : public AAragornBaseCharacter
{
	GENERATED_BODY()

public:
	AAragornHeroCharacter();

protected:
	// APawn Interface
	virtual void  PossessedBy(AController* NewController) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = true))
	TObjectPtr<UHeroCombatComponent> HeroCombatComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = CharacterData, meta = (AllowPrivateAccess = true))
	TObjectPtr<UDataAsset_InputConfig> InputConfigDataAsset;

private:
	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);

	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleased(FGameplayTag InInputTag);

public:
	FORCEINLINE UHeroCombatComponent* GetHeroCombatComponent() const { return HeroCombatComponent; }
};
