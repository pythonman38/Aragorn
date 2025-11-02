#pragma once

#include "CoreMinimal.h"

UENUM()
enum class EAragornConfirmType : uint8
{
	Yes,
	No
};

UENUM()
enum class EAragornValidType : uint8
{
	Valid,
	Invalid
};

UENUM()
enum class EAragornSuccessType : uint8
{
	Successful,
	Failed
};