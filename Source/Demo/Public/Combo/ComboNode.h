// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Combo/ActionStage.h"

#include "ComboNode.generated.h"




/**
 * 
 */
UCLASS(BlueprintType)
class DEMO_API UComboNode : public UObject
{
	GENERATED_BODY()
	

	UComboNode();

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int MaxActionIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CurrentActionIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TEnumAsByte<EComboActions> RootAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TEnumAsByte<EComboActions> Action;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TEnumAsByte<EActionStages> ActionStage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<int, UComboNode *> ChildComboMapping;

	UFUNCTION(BlueprintCallable)
	bool AddChildCombo(int ActionIndex, UComboNode *Combo);
};
