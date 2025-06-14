// Midnight Madness Inc. All Rights Reserved.


#include "AragornHeroCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Aragorn/AbilitySystem/AragornAbilitySystemComponent.h"
#include "Aragorn/Components/Combat/HeroCombatComponent.h"
#include "Aragorn/Components/HUD/HeroUIComponent.h"
#include "Aragorn/Components/Input/AragornInputComponent.h"
#include "Aragorn/DataAssets/Input/DataAsset_InputConfig.h"
#include "Aragorn/DataAssets/StartUpData/DataAsset_HeroStartupData.h"
#include "Aragorn/Singletons/AragornDebugHelper.h"
#include "Aragorn/Singletons/AragornGameplayTags.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


AAragornHeroCharacter::AAragornHeroCharacter() :
	SwitchDirection(FVector2D::ZeroVector)
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	HeroCompbatComponent = CreateDefaultSubobject<UHeroCombatComponent>("HeroCombatComp");
	HeroUIComponent = CreateDefaultSubobject<UHeroUIComponent>("HeroUI_Comp");

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

UPawnCombatComponent* AAragornHeroCharacter::GetPawnCombatComponent() const
{
	return HeroCompbatComponent;
}

UPawnUIComponent* AAragornHeroCharacter::GetPawnUIComponent() const
{
	return HeroUIComponent;
}

UHeroUIComponent* AAragornHeroCharacter::GetHeroUIComponent() const
{
	return HeroUIComponent;
}

void AAragornHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAragornHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("You forgot to assign a valid data asset as Input Config!"));
	auto LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(Subsystem);
	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
	auto AragornInputComponent = CastChecked<UAragornInputComponent>(PlayerInputComponent);
	AragornInputComponent->BindNativeInputAction(InputConfigDataAsset, AragornGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &AAragornHeroCharacter::Input_Move);
	AragornInputComponent->BindNativeInputAction(InputConfigDataAsset, AragornGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &AAragornHeroCharacter::Input_Look);
	AragornInputComponent->BindNativeInputAction(InputConfigDataAsset, AragornGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Triggered, this, &AAragornHeroCharacter::Input_SwitchTargetTriggered);
	AragornInputComponent->BindNativeInputAction(InputConfigDataAsset, AragornGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Completed, this, &AAragornHeroCharacter::Input_SwitchTargetCompleted);
	AragornInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &AAragornHeroCharacter::Input_AbilityInputPressed, &AAragornHeroCharacter::Input_AbilityInputReleased);
}

void AAragornHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!CharacterStartUpData.IsNull())
	{
		if (auto LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(AragornAbilitySystemComponent);
		}
	}
}

void AAragornHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation = FRotator(0.f, Controller->GetControlRotation().Yaw, 0.f);
	const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector), RightDirection = MovementRotation.RotateVector(FVector::RightVector);
	if (MovementVector.Y != 0.f) AddMovementInput(ForwardDirection, MovementVector.Y);
	if (MovementVector.X != 0.f) AddMovementInput(RightDirection, MovementVector.X);
}

void AAragornHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	if (LookAxisVector.X != 0.f) AddControllerYawInput(LookAxisVector.X);
	if (LookAxisVector.Y != 0.f) AddControllerPitchInput(LookAxisVector.Y);
}

void AAragornHeroCharacter::Input_SwitchTargetTriggered(const FInputActionValue& InputActionValue)
{
	SwitchDirection = InputActionValue.Get<FVector2D>();
}

void AAragornHeroCharacter::Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, SwitchDirection.X > 0.f ? AragornGameplayTags::Player_Event_SwitchTarget_Right :
		AragornGameplayTags::Player_Event_SwitchTarget_Left, Data);
}

void AAragornHeroCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	AragornAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void AAragornHeroCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	AragornAbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}
