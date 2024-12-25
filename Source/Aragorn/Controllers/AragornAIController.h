// Midnight Madness Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AragornAIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;

UCLASS()
class ARAGORN_API AAragornAIController : public AAIController
{
	GENERATED_BODY()

public:
	AAragornAIController(const FObjectInitializer& ObjectInitializer);

	// Inherited via IGenericTeamAgentInterface
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAIPerceptionComponent> EnemyPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAISenseConfig_Sight> AISenseConfig_Sight;

protected:
	UFUNCTION()
	virtual void OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = DetourCrowdAvoidanceConfig)
	bool bEnableDetourCrowdAvoidance;

	UPROPERTY(EditDefaultsOnly, Category = DetourCrowdAvoidanceConfig, meta = (EditCondition = bEnableDetourCrowdAvoidance, UIMin = 1, UIMax = 4))
	int32 DetourCrowdAvoidanceQuality;

	UPROPERTY(EditDefaultsOnly, Category = DetourCrowdAvoidanceConfig, meta = (EditCondition = bEnableDetourCrowdAvoidance))
	float CollisionQueryRange;
};
