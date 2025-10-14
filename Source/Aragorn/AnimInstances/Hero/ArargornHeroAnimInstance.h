// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "../AragornCharacterAnimInstance.h"
#include "ArargornHeroAnimInstance.generated.h"

class AAragornHeroCharacter;

UCLASS()
class ARAGORN_API UArargornHeroAnimInstance : public UAragornCharacterAnimInstance
{
	GENERATED_BODY()

public:
	UArargornHeroAnimInstance();
	
	virtual void NativeInitializeAnimation() override;

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|References")
	TObjectPtr<AAragornHeroCharacter> OwningHeroCharacter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bShouldEnterRelaxState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float EnterRelaxStateThreshold;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float IdleElapsedTime;
};
