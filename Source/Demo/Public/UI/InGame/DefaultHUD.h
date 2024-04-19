// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "UI/InGame/Settlement.h"

#include "DefaultHUD.generated.h"

/**
 * 
 */
class UCharacterStateHUD;
class AChert;
class USettlement;

UCLASS()
class DEMO_API ADefaultHUD : public AHUD
{
	GENERATED_BODY()

	ADefaultHUD();

	virtual void BeginPlay() override;
	
	TSubclassOf<UCharacterStateHUD> CharacterStateHUDRefence;
	UCharacterStateHUD *CharacterStateHUD;
	AChert *ChertRefence;

	TSubclassOf<USettlement> SettlementUIClassRef;
	USettlement *SettlementUI;

	UFUNCTION()
	void CreateSettlementUI(bool IsWin);

};
