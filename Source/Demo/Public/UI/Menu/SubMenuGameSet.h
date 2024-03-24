// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SubMenuGameSet.generated.h"

/**
 * 
 */

class UButton;
class UCheckBox;
class UComboBoxString;

UCLASS()
class DEMO_API USubMenuGameSet : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
	TObjectPtr<UButton> GameSet;

	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
	TObjectPtr<UButton> InputSet;

	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
	TObjectPtr<UButton> ScreenSet;

	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
	TObjectPtr<UButton> SoundSet;

	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
	TObjectPtr<UButton> GoBack;

	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
	TObjectPtr<UButton> GoBackMenu;


	// 画面设置
	UPROPERTY(BlueprintReadWrite, Category = "CheckBox", meta = (BindWidget))
	TObjectPtr<UCheckBox> FrameRateDisplay;

	UPROPERTY(BlueprintReadWrite, Category = "CheckBox", meta = (BindWidget))
	TObjectPtr<UCheckBox> VSync;

	UPROPERTY(BlueprintReadWrite, Category = "List", meta = (BindWidget))
	TObjectPtr<UComboBoxString> ResoRate;

	UPROPERTY(BlueprintReadWrite, Category = "List", meta = (BindWidget))
	TObjectPtr<UComboBoxString> GameWindowMode;

	UPROPERTY(BlueprintReadWrite, Category = "List", meta = (BindWidget))
	TObjectPtr<UComboBoxString> GameFrameLimit;

	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
	TObjectPtr<UButton> RestoreDefaultFrame;

	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
	TObjectPtr<UButton> AllowSet;

	// 输入设置
	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
	TObjectPtr<UButton> RestoreDefaultInput;
	
};
