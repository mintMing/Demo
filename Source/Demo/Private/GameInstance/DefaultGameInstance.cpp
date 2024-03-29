// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/DefaultGameInstance.h"

#include "GameFramework/GameUserSettings.h"
#include "InputMappingContext.h"



UDefaultGameInstance::UDefaultGameInstance()
{
	/*
	PlayerFrameSet.bDisplayFrames = false;
	PlayerFrameSet.bVSyn = false;
	PlayerFrameSet.ResolutionRatio.X = 1920;
	PlayerFrameSet.ResolutionRatio.Y = 1080;
	PlayerFrameSet.WMode = EWindowMode::Windowed;
	PlayerFrameSet.FramesLimint = FString("60");


	DefaultFramesSet.bDisplayFrames = false;
	DefaultFramesSet.bVSyn = false;
	DefaultFramesSet.ResolutionRatio.X = 1920;
	DefaultFramesSet.ResolutionRatio.Y = 1080;
	DefaultFramesSet.WMode = EWindowMode::Windowed;
	DefaultFramesSet.FramesLimint = FString("60");

	PlayerVolumeSet.TotalVolume = 1;
	PlayerVolumeSet.MusicVolume = 1;
	PlayerVolumeSet.SoundEffects = 1;
	*/
}
/*
void UDefaultGameInstance::LoadDisplaySet(const FFrameSetInfo &FrameSet)
{
	UGameUserSettings *UserSet = UGameUserSettings::GetGameUserSettings();

	if (UserSet)
	{
		UserSet->SetScreenResolution(FrameSet.ResolutionRatio);
		UserSet->SetFullscreenMode(FrameSet.WMode);
		if (FrameSet.FramesLimint == FString("ÎÞÏÞÖÆ"))
		{
			UserSet->SetFrameRateLimit(0);
		}
		else
		{
			UserSet->SetFrameRateLimit(FCString::Atoi(*FrameSet.FramesLimint));
		}
		UserSet->SetVSyncEnabled(FrameSet.bVSyn);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UserSet is null"));
	}
}
*/
