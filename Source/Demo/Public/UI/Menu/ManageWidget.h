// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Widgets/CommonActivatableWidgetContainer.h"

#include "ManageWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UManageWidget : public UUserWidget
{
	GENERATED_BODY()

public:


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WidgetStack")
	TSubclassOf<UCommonActivatableWidgetStack> WidgetStack;
	
};
