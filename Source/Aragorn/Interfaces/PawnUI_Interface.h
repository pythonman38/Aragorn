// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnUI_Interface.generated.h"

class UEnemyUI_Component;
class UHeroUI_Component;
class UPawnUI_Component;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPawnUI_Interface : public UInterface
{
	GENERATED_BODY()
};


class ARAGORN_API IPawnUI_Interface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UPawnUI_Component* GetPawnUI_Component() const = 0;

	virtual UHeroUI_Component* GetHeroUI_Component() const;

	virtual UEnemyUI_Component* GetEnemyUI_Component() const;
};
