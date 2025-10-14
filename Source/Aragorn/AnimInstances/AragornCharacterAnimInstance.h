// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "AragornBaseAnimInstance.h"
#include "AragornCharacterAnimInstance.generated.h"


class AAragornBaseCharacter;
class UCharacterMovementComponent;

UCLASS()
class ARAGORN_API UAragornCharacterAnimInstance : public UAragornBaseAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	TObjectPtr<AAragornBaseCharacter> OwningCharacter;

	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> OwningMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float GroundSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bHasAcceleration;
};
