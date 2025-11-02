// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AragornWidgetBase.generated.h"


class UEnemyUI_Component;
class UHeroUI_Component;

UCLASS()
class ARAGORN_API UAragornWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning Hero UI Component Initialized"))
	void BP_OnOwningHeroUI_ComponentInitialized(UHeroUI_Component* OwningHeroUI_Component);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning Enemy UI Component Initialized"))
	void BP_OnOwningEnemyUI_ComponentInitialized(UEnemyUI_Component* OwningEnemyUI_Component);

public:
	UFUNCTION(BlueprintCallable)
	void InitEnemyCreatedWidget(AActor* OwningEnemyActor);
};
