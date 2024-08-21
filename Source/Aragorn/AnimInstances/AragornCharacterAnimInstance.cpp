// Midnight Madness Inc. All Rights Reserved.


#include "AragornCharacterAnimInstance.h"

#include "Aragorn/Characters/AragornBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAragornCharacterAnimInstance::NativeInitializeAnimation()
{
	if (OwningCharacter = Cast<AAragornBaseCharacter>(TryGetPawnOwner()))
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UAragornCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent) return;

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}
