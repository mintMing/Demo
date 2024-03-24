// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "Struct/FrameSetInfo.h"

#include "DefaultGameInstance.generated.h"

/**
 * 
 */
struct FFrameSetInfo;
class UInputMappingContext;

UCLASS()
class DEMO_API UDefaultGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameSetInfo")
	FFrameSetInfo PlayerFrameSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameSetInfo")
	FFrameSetInfo DefaultFramesSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IMC")
	UInputMappingContext *DefaultIMC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IMC")
	UInputMappingContext *PlayerIMC;

public:
	UFUNCTION(BlueprintCallable)
	void LoadDisplaySet(const FFrameSetInfo &FrameSet);

	UFUNCTION(BlueprintCallable)
	void RestoreDefaulInputSet();
};
