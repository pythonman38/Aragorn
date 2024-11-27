// Midnight Madness Inc. All Rights Reserved.


#include "GE_ExecCalc_DamageTaken.h"

#include "Aragorn/AbilitySystem/AragornAttributeSet.h"
#include "Aragorn/Singletons/AragornGameplayTags.h"
#include "Aragorn/Singletons/AragornDebugHelper.h"

struct FAragornDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	FAragornDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAragornAttributeSet, AttackPower, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAragornAttributeSet, DefensePower, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAragornAttributeSet, DamageTaken, Target, false)
	}
};

static const FAragornDamageCapture& GetAragornDamageCapture()
{
	static FAragornDamageCapture AragornDamageCapture;
	return AragornDamageCapture;
}

UGE_ExecCalc_DamageTaken::UGE_ExecCalc_DamageTaken()
{
	RelevantAttributesToCapture.Add(GetAragornDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetAragornDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetAragornDamageCapture().DamageTakenDef);
}

void UGE_ExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const auto& EffectSpec = ExecutionParams.GetOwningSpec();
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetAragornDamageCapture().AttackPowerDef, EvaluateParameters, SourceAttackPower);

	float BaseDamage = 0.f;
	int32 UsedLightAttackComboCount = 0, UsedHeavyAttackComboCount = 0;
	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(AragornGameplayTags::Shared_SetByCaller_BaseDamage)) BaseDamage = TagMagnitude.Value;

		if (TagMagnitude.Key.MatchesTagExact(AragornGameplayTags::Player_SetByCaller_AttackType_Light)) UsedLightAttackComboCount = TagMagnitude.Value;

		if (TagMagnitude.Key.MatchesTagExact(AragornGameplayTags::Player_SetByCaller_AttackType_Heavy)) UsedHeavyAttackComboCount = TagMagnitude.Value;
	}

	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetAragornDamageCapture().DefensePowerDef, EvaluateParameters, TargetDefensePower);

	if (UsedLightAttackComboCount != 0)
	{
		const float DamageIncreasedPercentLight = (UsedLightAttackComboCount - 1) * 0.05f + 1.f;
		BaseDamage *= DamageIncreasedPercentLight;
	}

	if (UsedHeavyAttackComboCount != 0)
	{
		const float DamageIncreasedPercentHeavy = UsedHeavyAttackComboCount * 0.15f + 1.f;
		BaseDamage *= DamageIncreasedPercentHeavy;
	}

	const float FinalDamageDone = BaseDamage * SourceAttackPower / TargetDefensePower;
	auto OutputModifier = FGameplayModifierEvaluatedData(GetAragornDamageCapture().DamageTakenProperty, EGameplayModOp::Override, FinalDamageDone);
	if (FinalDamageDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(OutputModifier);
	}
}
