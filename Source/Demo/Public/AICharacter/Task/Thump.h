// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Thump.generated.h"


class ASamuraiController;
class ASamurai;

/**
 * 
 */
UCLASS()
class DEMO_API UThump : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory);

	ASamuraiController *AIController;

	ASamurai *AICharacter;

	FTimerHandle DelayThump;

	void EndThump();
};
