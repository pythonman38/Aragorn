// Midnight Madness, Inc.


#include "PawnUI_Interface.h"

// Add default functionality here for any IPawnUI_Interface functions that are not pure virtual.
UHeroUI_Component* IPawnUI_Interface::GetHeroUI_Component() const
{
	return nullptr;
}

UEnemyUI_Component* IPawnUI_Interface::GetEnemyUI_Component() const
{
	return nullptr;
}
