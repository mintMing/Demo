// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DefaultHUD.generated.h"

/**
 * 
 */
class UCharacterStateHUD;



UCLASS()
class DEMO_API ADefaultHUD : public AHUD
{
	GENERATED_BODY()

	ADefaultHUD();

	virtual void BeginPlay() override;

	TSubclassOf<UCharacterStateHUD> CharacterStateHUDClass;

	UCharacterStateHUD *CharacterStateHUD;
	
};
