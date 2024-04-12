// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/DefaultGameMode.h"

#include "Character/Chert.h"
#include "Controller/DefaultPlayerController.h"
#include "UI/InGame/DefaultHUD.h"

ADefaultGameMode::ADefaultGameMode()
{
	static ConstructorHelpers::FClassFinder<AChert> PlayerBPClass(TEXT("/Game/Blueprints/Character/BP_Chert"));
	if (PlayerBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerBPClass.Class;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PlayerBPClass is null"));
	}

	// 设置默认的玩家控制器类
	static ConstructorHelpers::FClassFinder<ADefaultPlayerController> PlayerControllerBPClass(TEXT("/Game/Blueprints/Controller/BP_PlayerController"));
	if (PlayerControllerBPClass.Class)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PlayerControllerBPClass is null"));
	}

	HUDClass = ADefaultHUD::StaticClass();
}
