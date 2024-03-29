// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VolumeSetInfo.generated.h"

USTRUCT(BlueprintType)
struct FVolumeSetInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameSetInfo")
	float TotalVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameSetInfo")
	float MusicVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameSetInfo")
	float SoundEffects;

};