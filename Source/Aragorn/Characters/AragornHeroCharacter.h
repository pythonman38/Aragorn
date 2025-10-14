// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "AragornBaseCharacter.h"
#include "AragornHeroCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UDataAsset_InputConfig;
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = CharacterData, meta = (AllowPrivateAccess = true))
	TObjectPtr<UDataAsset_InputConfig> InputConfigDataAsset;

private:
	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
};
