// Midnight Madness, Inc.


#include "AragornAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Aragorn/Components/UI/HeroUI_Component.h"
#include "Aragorn/Components/UI/PawnUI_Component.h"
#include "Aragorn/Interfaces/PawnUI_Interface.h"
#include "Aragorn/Singletons/AragornDebugHelper.h"
#include "Aragorn/Singletons/AragornFunctionLibrary.h"
#include "Aragorn/Singletons/AragornGameplayTags.h"

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
	
	checkf(CachedPawnUI_Interface.IsValid(), TEXT("%s didn't implement IPawnUI Interface"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());
	auto PawnUI_Component = CachedPawnUI_Interface->GetPawnUI_Component();
	checkf(PawnUI_Component, TEXT("Couldn't extract a PawnUI Component from %s"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());
	
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);
		PawnUI_Component->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
	}

	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		const float NewCurrentRage = FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage());
		SetCurrentRage(NewCurrentRage);
		if (auto HeroUI_Component = CachedPawnUI_Interface->GetHeroUI_Component())
		{
			HeroUI_Component->OnCurrentRageChanged.Broadcast(GetCurrentRage() / GetMaxRage());
		}
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth(), DamageDone = GetDamageTaken(), NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone, 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);

		const FString DebugString = FString::Printf(TEXT("Old Health: %f, Damage Done: %f, NewCurrentHealth: %f"), OldHealth, DamageDone, NewCurrentHealth);
		Debug::Print(DebugString, FColor::Green);

		PawnUI_Component->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());

		if (GetCurrentHealth() == 0.f)
		{
			UAragornFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), AragornGameplayTags::Shared_Status_Dead);
		}
	}
}
