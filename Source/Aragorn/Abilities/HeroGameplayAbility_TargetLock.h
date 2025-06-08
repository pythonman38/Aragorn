// Midnight Madness Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AragornHeroGameplayAbility.h"
#include "HeroGameplayAbility_TargetLock.generated.h"

class UAragornWidgetBase;
class UInputMappingContext;

UCLASS()
class ARAGORN_API UHeroGameplayAbility_TargetLock : public UAragornHeroGameplayAbility
{
	GENERATED_BODY()

public:
	UHeroGameplayAbility_TargetLock();

protected:
	/* Via UGameplayAbility Inteface */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	/* End UGameplayAbility Interface */

	UFUNCTION(BlueprintCallable)
	void OnTargetLockTick(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void SwitchTarget(const FGameplayTag& InSwitchDirectionTag);

private:
	void TryLockOnTarget();

	void GetAvailableActorsToLock();

	AActor* GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors);

	void GetAvailableActorsAroundTarget(TArray<AActor*>& OutActorsOnLeft, TArray<AActor*>& OutActorsOnRight);

	void DrawTargetLockWidget();

	void SetTargetLockWidgetPosition();

	void InitTargetLockMovement();

	void InitTargetLockMappingContext();

	/* Closing Functions */
	void CancelTargetLockAbility();

	void CleanUp();

	void ResetTargetLockMovement();

	void ResetTargetLockMappingContext();

private:
	UPROPERTY(EditDefaultsOnly, Category = TargetLock)
	float BoxTraceDistance;

	UPROPERTY(EditDefaultsOnly, Category = TargetLock)
	FVector TraceBoxSize;

	UPROPERTY(EditDefaultsOnly, Category = TargetLock)
	TArray<TEnumAsByte<EObjectTypeQuery>> BoxTraceChannel;

	UPROPERTY(EditDefaultsOnly, Category = TargetLock)
	bool bShowPersistentDebugShape;

	UPROPERTY(EditDefaultsOnly, Category = TargetLock)
	TSubclassOf<UAragornWidgetBase> TargetLockWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = TargetLock)
	float TargetLockMaxWalkSpeed;

	UPROPERTY(EditDefaultsOnly, Category = TargetLock)
	float TargetLockRotationInterpSpeed;

	UPROPERTY(EditDefaultsOnly, Category = TargetLock)
	TObjectPtr<UInputMappingContext> TargetLockMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = TargetLock)
	float TargetLockCameraOffsetDistance;

	UPROPERTY()
	TArray<AActor*> AvailableActorsToLock;

	UPROPERTY()
	AActor* CurrentLockedActor;

	UPROPERTY()
	TObjectPtr<UAragornWidgetBase> DrawnTargetLockWidget;

	UPROPERTY()
	FVector2D TargetLockWidgetSize;

	UPROPERTY()
	float CachedDefaultMaxWalkSpeed;
};
