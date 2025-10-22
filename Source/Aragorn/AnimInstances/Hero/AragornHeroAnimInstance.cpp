// Midnight Madness, Inc.


#include "AragornHeroAnimInstance.h"

#include "Aragorn/Characters/AragornHeroCharacter.h"

UAragornHeroAnimInstance::UAragornHeroAnimInstance() :
EnterRelaxStateThreshold(6.f)
{
}

void UAragornHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter) OwningHeroCharacter = Cast<AAragornHeroCharacter>(OwningCharacter);
}

void UAragornHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
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
