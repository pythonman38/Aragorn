// Midnight Madness Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AragornFunctionLibrary.generated.h"

class  UAragornAbilitySystemComponent;

UENUM()
enum class EAragornConfirmType : uint8
{
	Yes,
	No
};

UCLASS()
class ARAGORN_API UAragornFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	static UAragornAbilitySystemComponent* NativeGetAragornASCFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Aragorn|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category = "Aragorn|FunctionLibrary")
	static void RemoveGameplayFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	UFUNCTION(BlueprintCallable, Category = "Aragorn|FunctionLibrary", meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EAragornConfirmType& OutConfirmType);
};