// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/DefaultPlayerController.h"

#include "Character/Chert.h"
#include "UI/InGame/DefaultHUD.h"


//#include "Camera/DynamicCamera.h"

ADefaultPlayerController::ADefaultPlayerController()
{

}
/*
void ADefaultPlayerController::OpenAIUI()
{
	AChert *Player = Cast<AChert>(GetPawn());
	if (Player)
	{
		Player->FindAITargetPtr();
	}
	if (ADefaultHUD *HUD = Cast<ADefaultHUD>(GetHUD()))
	{
		HUD->CreateFightMainUI();
	}
}
*/
/*
void ADefaultPlayerController::OnPossess(APawn *aPawn)
{
	Super::OnPossess(aPawn);

	ADynamicCamera * DC = Cast<ADynamicCamera>(PlayerCameraManager);

	DC->SetPlayerControllerAndPlayerPawn(this, aPawn);

}
*/