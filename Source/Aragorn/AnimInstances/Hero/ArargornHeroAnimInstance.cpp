// Midnight Madness, Inc.


#include "ArargornHeroAnimInstance.h"

#include "Aragorn/Characters/AragornHeroCharacter.h"

UArargornHeroAnimInstance::UArargornHeroAnimInstance() :
EnterRelaxStateThreshold(6.f)
{
}

void UArargornHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter) OwningHeroCharacter = Cast<AAragornHeroCharacter>(OwningCharacter);
}

void UArargornHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (bHasAcceleration)
	{
		IdleElapsedTime = 0.f;
		bShouldEnterRelaxState = false;
	}
	else
	{
		IdleElapsedTime += DeltaSeconds;
		bShouldEnterRelaxState = (IdleElapsedTime >= EnterRelaxStateThreshold);
	}
}
