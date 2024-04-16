// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter/Task/Chase.h"

#include "AICharacter/SamuraiController.h"
#include "AICharacter/Samurai.h"

EBTNodeResult::Type UChase::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
	auto *AIController = Cast<ASamuraiController>(OwnerComp.GetAIOwner());
	if (IsValidChecked(AIController))
	{
		ASamurai *AICharacter = Cast<ASamurai>(AIController->GetPawn());
		if (AICharacter)
		{
			AICharacter->RunMovement(true);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
