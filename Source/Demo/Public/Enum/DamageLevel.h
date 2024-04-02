// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageLevel.generated.h"


UENUM(BlueprintType)
enum class EDamageLevel : uint8
{
	NONE,
	COMMON,   // ÆÕ¹¥
	BLEEDING  // ³öÑª
};
