// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ActionStage.generated.h"


UENUM(BlueprintType)
enum EComboActions : uint8
{
	Combo_1,
	Combo_1_1,
	Combo_1_2,
	Combo_1_3,
	Combo_1_4
};

UENUM(BlueprintType)
enum EActionStages : uint8
{
	Pre,
	Attack,
	Derive,
	Gap,
	End
};



// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UActionStage : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DEMO_API IActionStage
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Pre() = 0;
	virtual void Attack() = 0;
	virtual void Derive() = 0;
	virtual void Gap() = 0;
	virtual void End() = 0;
};