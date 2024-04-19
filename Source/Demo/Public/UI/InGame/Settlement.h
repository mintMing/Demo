// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Settlement.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API USettlement : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct();

	virtual void NativeTick(const FGeometry &MyGeometry, float InDeltaTime);

	// µ¹¼ÆÊ±
	int32 CountDownTime;

	float WaitTime;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetCountDownTime();

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetResultText(bool IsWin);

	UFUNCTION(BlueprintImplementableEvent)
	void SetCountDownText();
};