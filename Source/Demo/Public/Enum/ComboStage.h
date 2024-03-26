// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ComboStage.generated.h"

UENUM(BlueprintType)
enum class EComboStage :uint8
{
	PRE = 0,
	ATTACK = 1,
	DERIVE_START = 2,
	GAP = 3,
	DERIVE_END = 4,
	END = 5

};