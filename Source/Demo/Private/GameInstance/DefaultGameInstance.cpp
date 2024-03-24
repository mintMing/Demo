// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/DefaultGameInstance.h"

#include "GameFramework/GameUserSettings.h"
#include "InputMappingContext.h"

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

void UDefaultGameInstance::RestoreDefaulInputSet()
{
	const TArray < FEnhancedActionKeyMapping> &DefaultMappings = DefaultIMC->GetMappings();
	FEnhancedActionKeyMapping &DefaultMapping = DefaultIMC->GetMapping(0);

	const TArray<FEnhancedActionKeyMapping> &PlayerMappings = PlayerIMC->GetMappings();


	if (PlayerMappings.Num() == DefaultMappings.Num())
	{
		for (int i = 0; i < PlayerMappings.Num(); i++)
		{
			PlayerIMC->GetMapping(i) = DefaultIMC->GetMapping(i);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Array sizes mismatch. Unable to restore default input settings."));
	}
}
