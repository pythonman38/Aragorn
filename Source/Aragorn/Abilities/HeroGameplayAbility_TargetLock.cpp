// Midnight Madness Inc. All Rights Reserved.


#include "HeroGameplayAbility_TargetLock.h"

#include "Aragorn/Characters/AragornHeroCharacter.h"
#include "Aragorn/Controllers/AragornHeroController.h"
#include "Aragorn/Singletons/AragornDebugHelper.h"
#include "Aragorn/Singletons/AragornFunctionLibrary.h"
#include "Aragorn/Singletons/AragornGameplayTags.h"
#include "Aragorn/Widgets/AragornWidgetBase.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/SizeBox.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

UHeroGameplayAbility_TargetLock::UHeroGameplayAbility_TargetLock() :
	BoxTraceDistance(5000.f),
	TraceBoxSize(FVector(2000.f, 2000.f, 300.f)),
	bShowPersistentDebugShape(false),
	TargetLockWidgetSize(FVector2D::ZeroVector),
	TargetLockRotationInterpSpeed(5.f),
	CachedDefaultMaxWalkSpeed(0.f),
	TargetLockMaxWalkSpeed(200.f),
	TargetLockCameraOffsetDistance(20.f)
{
}

void UHeroGameplayAbility_TargetLock::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	TryLockOnTarget();
	InitTargetLockMovement();
	InitTargetLockMappingContext();

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UHeroGameplayAbility_TargetLock::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	ResetTargetLockMovement();
	ResetTargetLockMappingContext();
	CleanUp();

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UHeroGameplayAbility_TargetLock::OnTargetLockTick(float DeltaTime)
{
	if (!CurrentLockedActor
		|| UAragornFunctionLibrary::NativeDoesActorHaveTag(CurrentLockedActor, AragornGameplayTags::Shared_Status_Dead)
		|| UAragornFunctionLibrary::NativeDoesActorHaveTag(GetHeroCharacterFromActorInfo(), AragornGameplayTags::Shared_Status_Dead))
	{
		CancelTargetLockAbility();
		return;
	}

	SetTargetLockWidgetPosition();
	auto Hero = GetHeroCharacterFromActorInfo();
	auto HeroController = GetHeroControllerFromActorInfo();
	const bool bShouldOverrideRotation = !UAragornFunctionLibrary::NativeDoesActorHaveTag(Hero, AragornGameplayTags::Player_Status_Rolling) &&
		!UAragornFunctionLibrary::NativeDoesActorHaveTag(Hero, AragornGameplayTags::Player_Status_Blocking);

	if (bShouldOverrideRotation)
	{
		FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(Hero->GetActorLocation(), CurrentLockedActor->GetActorLocation());
		LookAtRot -= FRotator(TargetLockCameraOffsetDistance, 0.f, 0.f);

		const FRotator CurrentControlRot = Hero->GetControlRotation(),
			TargetRot = FMath::RInterpTo(CurrentControlRot, LookAtRot, DeltaTime, TargetLockRotationInterpSpeed);
		HeroController->SetControlRotation(FRotator(TargetRot.Pitch, TargetRot.Yaw, 0.f));
		Hero->SetActorRotation(FRotator(0.f, TargetRot.Yaw, 0.f));
	}
}

void UHeroGameplayAbility_TargetLock::SwitchTarget(const FGameplayTag& InSwitchDirectionTag)
{
	GetAvailableActorsToLock();
	TArray<AActor*> ActorsOnLeft, ActorsOnRight;
	AActor* NewTargetToLock = nullptr;
	GetAvailableActorsAroundTarget(ActorsOnLeft, ActorsOnRight);
	if (InSwitchDirectionTag == AragornGameplayTags::Player_Event_SwitchTarget_Left)
	{
		NewTargetToLock = GetNearestTargetFromAvailableActors(ActorsOnLeft);
	}
	else NewTargetToLock = GetNearestTargetFromAvailableActors(ActorsOnRight);

	if (NewTargetToLock) CurrentLockedActor = NewTargetToLock;
}

void UHeroGameplayAbility_TargetLock::TryLockOnTarget()
{
	GetAvailableActorsToLock();

	if (AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}

	CurrentLockedActor = GetNearestTargetFromAvailableActors(AvailableActorsToLock);
	if (CurrentLockedActor)
	{
		DrawTargetLockWidget();
		SetTargetLockWidgetPosition();
	}
	else CancelTargetLockAbility();

}

void UHeroGameplayAbility_TargetLock::GetAvailableActorsToLock()
{
	AvailableActorsToLock.Empty();
	TArray<FHitResult> BoxTraceHits;
	const auto Hero = GetHeroCharacterFromActorInfo();
	const auto HeroLocation = Hero->GetActorLocation(), HeroForwardVector = Hero->GetActorForwardVector();
	UKismetSystemLibrary::BoxTraceMultiForObjects(Hero, HeroLocation, HeroLocation + HeroForwardVector * BoxTraceDistance, TraceBoxSize / 2.f, HeroForwardVector.ToOrientationRotator(),
		BoxTraceChannel, false, TArray<AActor*>(), bShowPersistentDebugShape ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None, BoxTraceHits, true);

	for (const FHitResult& TraceHit : BoxTraceHits)
	{
		if (auto HitActor = TraceHit.GetActor())
		{
			if (HitActor != Hero) AvailableActorsToLock.AddUnique(HitActor);
		}
	}
}

AActor* UHeroGameplayAbility_TargetLock::GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors)
{
	float ClosestDistance = 0.f;
	return UGameplayStatics::FindNearestActor(GetHeroCharacterFromActorInfo()->GetActorLocation(), InAvailableActors, ClosestDistance);
}

void UHeroGameplayAbility_TargetLock::GetAvailableActorsAroundTarget(TArray<AActor*>& OutActorsOnLeft, TArray<AActor*>& OutActorsOnRight)
{
	if (!CurrentLockedActor || AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}

	const FVector PlayerLocation = GetHeroCharacterFromActorInfo()->GetActorLocation(), 
		PlayerToCurrentNormalized = (CurrentLockedActor->GetActorLocation() - PlayerLocation).GetSafeNormal();
	for (AActor* AvailableActor : AvailableActorsToLock)
	{
		if (!AvailableActor || AvailableActor == CurrentLockedActor) continue;

		const FVector PlayerToAvailableNormalized = (AvailableActor->GetActorLocation() - PlayerLocation).GetSafeNormal(),
			CrossResult = FVector::CrossProduct(PlayerToCurrentNormalized, PlayerToAvailableNormalized);

		if (CrossResult.Z > 0.f) OutActorsOnRight.AddUnique(AvailableActor);
		else OutActorsOnLeft.AddUnique(AvailableActor);
	}
}

void UHeroGameplayAbility_TargetLock::DrawTargetLockWidget()
{
	if (DrawnTargetLockWidget) return;

	checkf(TargetLockWidgetClass, TEXT("Forgot to assign a valid widget class in Blueprint"));
	DrawnTargetLockWidget = CreateWidget<UAragornWidgetBase>(GetHeroControllerFromActorInfo(), TargetLockWidgetClass);

	check(DrawnTargetLockWidget);
	DrawnTargetLockWidget->AddToViewport();
}

void UHeroGameplayAbility_TargetLock::SetTargetLockWidgetPosition()
{
	if (!DrawnTargetLockWidget || !CurrentLockedActor)
	{
		CancelTargetLockAbility();
		return;
	}

	FVector2D ScreenPosition;
	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(GetHeroControllerFromActorInfo(), CurrentLockedActor->GetActorLocation(), ScreenPosition, true);

	if (TargetLockWidgetSize == FVector2D::ZeroVector)
	{
		DrawnTargetLockWidget->WidgetTree->ForEachWidget([this](UWidget* FoundWidget)
			{
				if (auto FoundSizeBox = Cast<USizeBox>(FoundWidget))
				{
					TargetLockWidgetSize.X = FoundSizeBox->GetWidthOverride();
					TargetLockWidgetSize.Y = FoundSizeBox->GetHeightOverride();
				}
			});
	}
	ScreenPosition -= (TargetLockWidgetSize / 2.f);
	DrawnTargetLockWidget->SetPositionInViewport(ScreenPosition, false);
}

void UHeroGameplayAbility_TargetLock::InitTargetLockMovement()
{
	CachedDefaultMaxWalkSpeed = GetHeroCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed;
	GetHeroCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = TargetLockMaxWalkSpeed;
}

void UHeroGameplayAbility_TargetLock::InitTargetLockMappingContext()
{
	const auto LocalPlayer = GetHeroControllerFromActorInfo()->GetLocalPlayer();
	auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(Subsystem);
	Subsystem->AddMappingContext(TargetLockMappingContext, 3);
}

void UHeroGameplayAbility_TargetLock::CancelTargetLockAbility()
{
	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
}

void UHeroGameplayAbility_TargetLock::CleanUp()
{
	AvailableActorsToLock.Empty();
	CurrentLockedActor = nullptr;
	if (DrawnTargetLockWidget) DrawnTargetLockWidget->RemoveFromParent();

	DrawnTargetLockWidget = nullptr;
	TargetLockWidgetSize = FVector2D::ZeroVector;
	CachedDefaultMaxWalkSpeed = 0.f;
}

void UHeroGameplayAbility_TargetLock::ResetTargetLockMovement()
{
	if (CachedDefaultMaxWalkSpeed > 0.f)
	{
		GetHeroCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = CachedDefaultMaxWalkSpeed;
	}
}

void UHeroGameplayAbility_TargetLock::ResetTargetLockMappingContext()
{
	if (!GetHeroControllerFromActorInfo()) return;

	const auto LocalPlayer = GetHeroControllerFromActorInfo()->GetLocalPlayer();
	auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(Subsystem);
	Subsystem->RemoveMappingContext(TargetLockMappingContext);
}
