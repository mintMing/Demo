// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter/Task/Attack.h"

#include "AICharacter/SamuraiController.h"
#include "AICharacter/Samurai.h"

EBTNodeResult::Type UAttack::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
	
	ASamuraiController *AIController = Cast<ASamuraiController>(OwnerComp.GetAIOwner());
	if (!IsValid(AIController))
	{
		UE_LOG(LogTemp, Error, TEXT("AttackTaskNode: AIController is nullptr."));
		return EBTNodeResult::Failed;
	}

	ASamurai *Samurai = Cast<ASamurai>(AIController->GetPawn());
	if (!IsValid(Samurai))
	{
		UE_LOG(LogTemp, Error, TEXT("AttackTaskNode: AISamurai is nullptr."));
		return EBTNodeResult::Failed;
	}

	Samurai->Attack();
	return EBTNodeResult::Succeeded;
	
	return EBTNodeResult::Succeeded;
}