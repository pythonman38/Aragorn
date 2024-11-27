// Midnight Madness Inc. All Rights Reserved.


#include "AragornEnemyCharacter.h"

#include "Aragorn/Components/Combat/EnemyCombatComponent.h"
#include "Aragorn/Components/HUD/EnemyUIComponent.h"
#include "Aragorn/DataAssets/StartUpData/DataAsset_EnemyStartUpData.h"
#include "Aragorn/Singletons/AragornDebugHelper.h"
#include "Aragorn/Widgets/AragornWidgetBase.h"
#include "Components/WidgetComponent.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"

AAragornEnemyCharacter::AAragornEnemyCharacter()
{
	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>("EnemyCombatComponent");

	EnemyUIComponent = CreateDefaultSubobject<UEnemyUIComponent>("EnemyUI_Component");

	EnemyHealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("EnemyHealthWidgetComponent");
	EnemyHealthWidgetComponent->SetupAttachment(GetMesh());

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;
}

UPawnCombatComponent* AAragornEnemyCharacter::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

UPawnUIComponent* AAragornEnemyCharacter::GetPawnUIComponent() const
{
	return EnemyUIComponent;
}

UEnemyUIComponent* AAragornEnemyCharacter::GetEnemyUIComponent() const
{
	return EnemyUIComponent;
}

void AAragornEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (auto HealthWidget = Cast<UAragornWidgetBase>(EnemyHealthWidgetComponent->GetUserWidgetObject()))
	{
		HealthWidget->InitEnemyCreatedWidget(this);
	}
}

void AAragornEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitEnemyStartupData();
}

void AAragornEnemyCharacter::InitEnemyStartupData()
{
	if (CharacterStartUpData.IsNull()) return;

	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this]()
			{
				if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.Get()) LoadedData->GiveToAbilitySystemComponent(AragornAbilitySystemComponent);
			}
		)
	);
}
