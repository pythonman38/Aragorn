// Midnight Madness, Inc.


#include "AragornWidgetBase.h"

#include "Aragorn/Interfaces/PawnUI_Interface.h"

void UAragornWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (IPawnUI_Interface* PawnUI_Interface = Cast<IPawnUI_Interface>(GetOwningPlayerPawn()))
	{
		if (auto HeroUI_Component = PawnUI_Interface->GetHeroUI_Component())
		{
			BP_OnOwningHeroUI_ComponentInitialized(HeroUI_Component);
		}
	}
}

void UAragornWidgetBase::InitEnemyCreatedWidget(AActor* OwningEnemyActor)
{
	if (IPawnUI_Interface* PawnUI_Interface = Cast<IPawnUI_Interface>(OwningEnemyActor))
	{
		auto EnemyUI_Component = PawnUI_Interface->GetEnemyUI_Component();
		checkf(EnemyUI_Component, TEXT("Failed to extract an Enemy UI Component from %s!"), *OwningEnemyActor->GetActorNameOrLabel());
		BP_OnOwningEnemyUI_ComponentInitialized(EnemyUI_Component);
	}
}
