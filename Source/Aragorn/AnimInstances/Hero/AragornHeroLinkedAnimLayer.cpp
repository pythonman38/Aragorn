// Midnight Madness, Inc.


#include "AragornHeroLinkedAnimLayer.h"

#include "AragornHeroAnimInstance.h"

UAragornHeroAnimInstance* UAragornHeroLinkedAnimLayer::GetHeroAnimInstance() const
{
	return Cast<UAragornHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
