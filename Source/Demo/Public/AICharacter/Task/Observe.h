// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Observe.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UObserve : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory);
};
