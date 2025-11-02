// Midnight Madness, Inc.


#include "AragornEnemyCharacter.h"

#include "Aragorn/Components/Combat/EnemyCombatComponent.h"
#include "Aragorn/Components/UI/EnemyUI_Component.h"
#include "Aragorn/DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "Aragorn/Widgets/AragornWidgetBase.h"
#include "Components/WidgetComponent.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"

AAragornEnemyCharacter::AAragornEnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 180.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>("EnemyCombatComp");
	EnemyUI_Component = CreateDefaultSubobject<UEnemyUI_Component>("EnemyUI_Comp");
	EnemyHealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("EnemyHealthWidgetComp");
	EnemyHealthWidgetComponent->SetupAttachment(GetMesh());
}

UPawnCombatComponent* AAragornEnemyCharacter::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

UPawnUI_Component* AAragornEnemyCharacter::GetPawnUI_Component() const
{
	return EnemyUI_Component;
}

UEnemyUI_Component* AAragornEnemyCharacter::GetEnemyUI_Component() const
{
	return EnemyUI_Component;
}

void AAragornEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (UAragornWidgetBase* HealthWidget = Cast<UAragornWidgetBase>(EnemyHealthWidgetComponent->GetUserWidgetObject()))
	{
		HealthWidget->InitEnemyCreatedWidget(this);
	}
}

void AAragornEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitEnemyStartUpData();
}

void AAragornEnemyCharacter::InitEnemyStartUpData() const
{
	if (CharacterStartUpData.IsNull()) return;

	UAssetManager::GetStreamableManager().RequestAsyncLoad(CharacterStartUpData.ToSoftObjectPath(), FStreamableDelegate::CreateLambda(
		[this]()
		{
			if (auto LoadedData = CharacterStartUpData.Get()) LoadedData->GiveToAbilitySystemComponent(AragornAbilitySystemComponent);
		}
	));
}
