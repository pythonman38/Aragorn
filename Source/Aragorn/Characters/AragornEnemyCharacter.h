// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "AragornBaseCharacter.h"
#include "AragornEnemyCharacter.generated.h"


class UWidgetComponent;
class UEnemyUI_Component;
class UEnemyCombatComponent;

UCLASS()
class ARAGORN_API AAragornEnemyCharacter : public AAragornBaseCharacter
{
	GENERATED_BODY()

public:
	AAragornEnemyCharacter();

	// IPawnCombatInterface Interface
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;

	// IPawnUI_Interface Interface
	virtual UPawnUI_Component* GetPawnUI_Component() const override;
	virtual UEnemyUI_Component* GetEnemyUI_Component() const override;

protected:
	virtual void BeginPlay() override;
	
	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat)
	TObjectPtr<UEnemyCombatComponent> EnemyCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI)
	TObjectPtr<UEnemyUI_Component> EnemyUI_Component;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI)
	TObjectPtr<UWidgetComponent> EnemyHealthWidgetComponent;

private:
	void InitEnemyStartUpData() const;

public:
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }
};
