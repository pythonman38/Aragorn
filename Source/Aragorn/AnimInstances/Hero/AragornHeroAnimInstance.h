// Midnight Madness Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Aragorn/AnimInstances/AragornCharacterAnimInstance.h"
#include "AragornHeroAnimInstance.generated.h"

class AAragornHeroCharacter;

UCLASS()
class ARAGORN_API UAragornHeroAnimInstance : public UAragornCharacterAnimInstance
{
	GENERATED_BODY()
	
public:
	UAragornHeroAnimInstance();

	virtual void NativeInitializeAnimation() override;

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	float IdleElapsedTime;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bShouldEnterRelaxState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float EnterRelaxStateThreshold;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|References")
	TObjectPtr<AAragornHeroCharacter> OwningHeroCharacter;
};
