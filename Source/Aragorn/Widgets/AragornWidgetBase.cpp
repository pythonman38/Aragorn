// Midnight Madness Inc. All Rights Reserved.


#include "AragornWidgetBase.h"

#include "Aragorn/Interfaces/PawnUI_Interface.h"

void UAragornWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (auto PawnUI_Interface = Cast<IPawnUI_Interface>(GetOwningPlayerPawn()))
	{
		if (auto HeroUIComponent = PawnUI_Interface->GetHeroUIComponent())
		{
			BP_OnOwningHeroUIComponentInitialized(HeroUIComponent);
		}
	}
}

void UAragornWidgetBase::InitEnemyCreatedWidget(AActor* OwningEnemyActor)
{
	if (auto PawnUI_Interface = Cast<IPawnUI_Interface>(OwningEnemyActor))
	{
		auto EnemyUIComponent = PawnUI_Interface->GetEnemyUIComponent();

		checkf(EnemyUIComponent, TEXT("Failed to extract an EnemyUIComponent from %s"), *OwningEnemyActor->GetActorNameOrLabel());

		BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
	}
}
