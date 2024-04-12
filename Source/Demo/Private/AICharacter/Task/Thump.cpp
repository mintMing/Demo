// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter/Task/Thump.h"

#include "AICharacter/SamuraiController.h"
#include "AICharacter/Samurai.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UThump::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
	AIController = Cast<ASamuraiController>(OwnerComp.GetAIOwner());
	if (IsValidChecked(AIController))
	{
		AICharacter = Cast<ASamurai>(AIController->GetPawn());

		if (IsValidChecked(AICharacter))
		{
			if (!AIController->GetBlackboardComponent()->GetValueAsBool("ThumpDoOnce"))
			{
				AIController->GetBlackboardComponent()->SetValueAsBool("ThumpDoOnce", true);

				// ÆôÓÃTick 
				AICharacter->SetActorTickEnabled(true);

				GetWorld()->GetTimerManager().SetTimer(DelayThump, this, &UThump::EndThump,
					UKismetMathLibrary::RandomFloatInRange(5.f, 10.f), false, UKismetMathLibrary::RandomFloatInRange(5.f, 10.f));
			}
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}

void UThump::EndThump()
{
	AIController->GetBlackboardComponent()->SetValueAsBool("IsThump", false);

	AIController->GetBlackboardComponent()->SetValueAsBool("ThumpDoOnce", false);

	AICharacter->SetActorTickEnabled(false);

	AICharacter->RushThump();
}

