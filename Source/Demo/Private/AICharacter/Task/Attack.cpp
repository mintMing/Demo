// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter/Task/Attack.h"

#include "AICharacter/SamuraiController.h"
#include "AICharacter/Samurai.h"

EBTNodeResult::Type UAttack::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
	
	ASamuraiController *AIController = Cast<ASamuraiController>(OwnerComp.GetAIOwner());
	if (AIController)
	{
		ASamurai *Samurai = Cast<ASamurai>(AIController->GetPawn());
		if (Samurai)
		{
			Samurai->Attack();
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}