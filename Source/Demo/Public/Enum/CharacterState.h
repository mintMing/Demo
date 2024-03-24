// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterState.generated.h"



UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	NONE,
	WALK,			//����
	IDLE,			//����
	ATTACK,			//����
	RUN,			//����
	ROLLING,		//����
	SLIDE,			//����
	DEFENSE,		//����
	AFFECTED		//�ܻ�
};

