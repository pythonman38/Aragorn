// Midnight Madness, Inc.


#include "AragornCharacterAnimInstance.h"

#include "Aragorn/Characters/AragornBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAragornCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AAragornBaseCharacter>(TryGetPawnOwner());
	if (OwningCharacter) OwningMovementComponent = OwningCharacter->GetCharacterMovement();
}

void UAragornCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent) return;

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().Size2D() > 0.f;
}
