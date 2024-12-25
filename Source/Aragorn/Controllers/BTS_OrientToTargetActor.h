// Midnight Madness Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_OrientToTargetActor.generated.h"

UCLASS()
class ARAGORN_API UBTS_OrientToTargetActor : public UBTService
{
	GENERATED_BODY()

	UBTS_OrientToTargetActor();

	// Inherited via UBTNodeInterface
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual FString GetStaticDescription() const override;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = Target)
	FBlackboardKeySelector InTargetActorKey;

	UPROPERTY(EditAnywhere, Category = Target)
	float RotationInterpSpeed;
	
};
