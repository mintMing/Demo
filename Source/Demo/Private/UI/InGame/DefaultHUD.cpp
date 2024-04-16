// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/DefaultHUD.h"


#include "UI/InGame/CharacterStateHUD.h"

ADefaultHUD::ADefaultHUD()
{
	/*
	static ConstructorHelpers::FClassFinder<UCharacterStateHUD> CharacterStateUIClass(TEXT("/Game/Blueprints/UI/InGame/BP_CharacterStateHUD"));

	CharacterStateHUDRefence = CharacterStateUIClass.Class;
	*/
}

void ADefaultHUD::BeginPlay()
{
	Super::BeginPlay();
}
