// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter/Task/Observe.h"

#include "AICharacter/SamuraiController.h"
#include "Character/Character_Base.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UObserve::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
	ASamuraiController *AIController = Cast<ASamuraiController>(OwnerComp.GetAIOwner());
	check(AIController);

	ACharacter_Base *Player = Cast<ACharacter_Base>(AIController->GetBlackboardComponent()->GetValueAsObject("TarPlayer"));
	check(Player);

	AIController->SetFocus(Player);
	return EBTNodeResult::Succeeded;
}
