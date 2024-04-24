// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/DefaultHUD.h"


#include "UI/InGame/CharacterStateHUD.h"
#include "UI/InGame/Settlement.h"
#include "Entrusted/EventManager.h"

ADefaultHUD::ADefaultHUD()
{
	/*
	static ConstructorHelpers::FClassFinder<UCharacterStateHUD> CharacterStateUIClass(TEXT("/Game/Blueprints/UI/InGame/BP_CharacterStateHUD"));

	CharacterStateHUDRefence = CharacterStateUIClass.Class;
	*/

	static ConstructorHelpers::FClassFinder<USettlement> SettlementUIClass(TEXT("/Game/Blueprints/UI/InGame/BP_Settlement"));
	SettlementUIClassRef = SettlementUIClass.Class;
}

void ADefaultHUD::BeginPlay()
{
	Super::BeginPlay();

	UEventManager::GetInstancePtr()->OpenUI.BindUObject(this, &ADefaultHUD::CreateSettlementUI);

}

void ADefaultHUD::CreateSettlementUI(bool IsWin)
{
	SettlementUI = CreateWidget<USettlement>(GetWorld(), SettlementUIClassRef);
	SettlementUI->SetResultText(IsWin);
	SettlementUI->AddToViewport(0);
}


