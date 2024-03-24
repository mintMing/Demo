// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GenericPlatform/GenericWindow.h"
#include "Math/IntPoint.h"
#include "Engine/EngineTypes.h" // Include this for EWindowMode

#include "FrameSetInfo.generated.h"

USTRUCT(BlueprintType)
struct FFrameSetInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameSetInfo")
	bool bDisplayFrames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameSetInfo")
	FIntPoint ResolutionRatio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameSetInfo")
	TEnumAsByte<EWindowMode::Type> WMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameSetInfo")
	FString FramesLimint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameSetInfo")
	bool bVSyn;
};