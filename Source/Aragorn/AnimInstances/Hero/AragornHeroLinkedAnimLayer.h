// Midnight Madness Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Aragorn/AnimInstances/AragornBaseAnimInstance.h"
#include "AragornHeroLinkedAnimLayer.generated.h"

class UAragornHeroAnimInstance;

UCLASS()
class ARAGORN_API UAragornHeroLinkedAnimLayer : public UAragornBaseAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	UAragornHeroAnimInstance* GetHeroAnimInstance() const;
	
};
