// Midnight Madness Inc. All Rights Reserved.


#include "PawnUI_Interface.h"

// Add default functionality here for any IPawnUI_Interface functions that are not pure virtual.

UHeroUIComponent* IPawnUI_Interface::GetHeroUIComponent() const
{
    return nullptr;
}

UEnemyUIComponent* IPawnUI_Interface::GetEnemyUIComponent() const
{
    return nullptr;
}
