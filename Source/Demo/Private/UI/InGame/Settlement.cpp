// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Settlement.h"

#include "Kismet/GameplayStatics.h"
#include "GameInstance/DefaultGameInstance.h"

void USettlement::NativeConstruct()
{
	Super::NativeConstruct();

	CountDownTime = 5;

	WaitTime = 0.f;

	SetCountDownText();
}

void USettlement::NativeTick(const FGeometry &MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (CountDownTime > 0)
	{
		WaitTime = WaitTime + InDeltaTime;
		if (WaitTime >= 1)
		{
			CountDownTime--;
			SetCountDownText();
			WaitTime = 0;
		}
		if (CountDownTime == 0)
		{
			UGameplayStatics::OpenLevel(GetWorld(), "Main");
		}
	}
}

int32 USettlement::GetCountDownTime()
{
	return CountDownTime;
}

