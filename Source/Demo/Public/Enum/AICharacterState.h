// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AICharacterState.generated.h"



UENUM(BlueprintType)
enum class EAICharacterState : uint8
{
	NONE,
	IDLE,		 //¿ÕÏÐ
	ATTACK,		 //¹¥»÷
	ROLLING,	 //·­¹ö
	AFFECTED,	//ÊÜ»÷
	WATCH,		// ¹Û²ì
	CHASE,		// ×·»÷
	ACCUMULATEPOWER,	// ÐîÁ¦
};
