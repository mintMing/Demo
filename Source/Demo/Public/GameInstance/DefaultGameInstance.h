// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "Struct/FrameSetInfo.h"
#include "Struct/VolumeSetInfo.h"

#include "DefaultGameInstance.generated.h"

/**
 * 
 */
struct FFrameSetInfo;
struct FVolumeSetInfo;
class UInputMappingContext;

UCLASS()
class DEMO_API UDefaultGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UDefaultGameInstance();
	
public:
	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameSetInfo")
	FFrameSetInfo PlayerFrameSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameSetInfo")
	FFrameSetInfo DefaultFramesSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameSetInfo")
	FVolumeSetInfo PlayerVolumeSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameSetInfo")
	FVolumeSetInfo DefaultVolumeSet;
	*/

public:
	/*
	UFUNCTION(BlueprintCallable)
	void LoadDisplaySet(const FFrameSetInfo &FrameSet);
	*/
};
