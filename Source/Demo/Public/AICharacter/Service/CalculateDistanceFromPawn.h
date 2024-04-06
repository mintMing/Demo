// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CalculateDistanceFromPawn.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UCalculateDistanceFromPawn : public UBTService
{
	GENERATED_BODY()
	
	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;
};
