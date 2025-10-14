// Midnight Madness, Inc.


#include "AragornHeroCharacter.h"

#include "Aragorn/Components/Input/AragornInputComponent.h"
#include "Aragorn/DataAssets/Input/DataAsset_InputConfig.h"
#include "Aragorn/Singletons/AragornGameplayTags.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Aragorn/AbilitySystem/AragornAbilitySystemComponent.h"
#include "Aragorn/DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AAragornHeroCharacter::AAragornHeroCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 250.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 55.0f, 65.0f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
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

void AAragornHeroCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset as Input Config!"));
	auto LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(Subsystem);
	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
	auto AragornInputComponent = CastChecked<UAragornInputComponent>(PlayerInputComponent);
	AragornInputComponent->BindNativeInputAction(InputConfigDataAsset, AragornGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &AAragornHeroCharacter::Input_Move);
	AragornInputComponent->BindNativeInputAction(InputConfigDataAsset, AragornGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &AAragornHeroCharacter::Input_Look);
}

void AAragornHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAragornHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AAragornHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	if (LookAxisVector.X != 0.f) AddControllerYawInput(LookAxisVector.X);
	if (LookAxisVector.Y != 0.f) AddControllerPitchInput(LookAxisVector.Y);
}
