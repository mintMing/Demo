// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Combo/ComboNode.h"

#include "ComboContext.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class DEMO_API UComboContext : public UObject
{
	GENERATED_BODY()
	
	UComboContext();
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UComboNode *CurrentComboAction;

	UComboNode *FindRootCombo(EComboActions RootCombo);

private:

	UPROPERTY()
	TMap<TEnumAsByte<EComboActions>, UComboNode *> ComboMapping;
};
