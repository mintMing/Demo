// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */

class UButton;

UCLASS()
class DEMO_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> StartGame_Button;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> ExitGame_Button;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> Setting_Button;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> AboutGames_Button;
	
};
