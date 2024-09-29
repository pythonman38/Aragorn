// Midnight Madness Inc. All Rights Reserved.


#include "AragornHeroLinkedAnimLayer.h"

#include "Aragorn/AnimInstances/Hero/AragornHeroAnimInstance.h"

UAragornHeroAnimInstance* UAragornHeroLinkedAnimLayer::GetHeroAnimInstance() const
{
	return Cast<UAragornHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
