// Midnight Madness Inc. All Rights Reserved.


#include "AragornAttributeSet.h"

#include "Aragorn/Components/HUD/HeroUIComponent.h"
#include "Aragorn/Components/HUD/PawnUIComponent.h"
#include "Aragorn/Interfaces/PawnUI_Interface.h"
#include "Aragorn/Singletons/AragornDebugHelper.h"
#include "Aragorn/Singletons/AragornFunctionLibrary.h"
#include "Aragorn/Singletons/AragornGameplayTags.h"
#include "GameplayEffectExtension.h"

UAragornAttributeSet::UAragornAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentRage(1.f);
	InitMaxRage(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
}

void UAragornAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (!CachedPawnUI_Interface.IsValid())
	{
		CachedPawnUI_Interface = TWeakInterfacePtr<IPawnUI_Interface>(Data.Target.GetAvatarActor());
	}

	checkf(CachedPawnUI_Interface.IsValid(), TEXT("%s didn't implement Pawn UI Interface"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

	auto PawnUIComponent = CachedPawnUI_Interface->GetPawnUIComponent();

	checkf(PawnUIComponent, TEXT("Couldn't extract a Pawn UI Component from %s"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);
		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
	}

	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		const float NewCurrentRage = FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage());
		SetCurrentRage(NewCurrentRage);
		
		if (auto HeroUIComponent = CachedPawnUI_Interface->GetHeroUIComponent())
		{
			HeroUIComponent->OnCurrentRageChanged.Broadcast(GetCurrentRage() / GetMaxRage());
		}
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth(), DamageDone = GetDamageTaken();
		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone, 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);

		const FString DebugString = FString::Printf(TEXT("Old Health: %f, Damage Done: %f, NewCurrentHealth: %f"), OldHealth, DamageDone, NewCurrentHealth);
		Debug::Print(DebugString, FColor::Green);

		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());

		if (GetCurrentHealth() == 0.f)
		{
			UAragornFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), AragornGameplayTags::Shared_Status_Dead);
		}
	}
}
