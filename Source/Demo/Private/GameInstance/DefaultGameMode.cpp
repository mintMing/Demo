// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/DefaultGameMode.h"

#include "Character/Chert.h"
#include "Controller/DefaultPlayerController.h"
#include "UI/InGame/DefaultHUD.h"

ADefaultGameMode::ADefaultGameMode()
{
 	static ConstructorHelpers::FClassFinder<AChert> PlayerBPClass(TEXT("/Game/Blueprints/Character/BP_Chert"));
	check(PlayerBPClass.Class);
	if (PlayerBPClass.Class)
	{
		DefaultPawnClass = PlayerBPClass.Class;
	}

	// 设置默认的玩家控制器类
	static ConstructorHelpers::FClassFinder<ADefaultPlayerController> PlayerControllerBPClass(TEXT("/Game/Blueprints/Controller/BP_PlayerController"));
	if (PlayerControllerBPClass.Class)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<ADefaultHUD> DefaultHUDClass(TEXT("/Game/Blueprints/UI/InGame/BP_InGame"));
	if (DefaultHUDClass.Class)
	{
		HUDClass = DefaultHUDClass.Class;
	}


}
