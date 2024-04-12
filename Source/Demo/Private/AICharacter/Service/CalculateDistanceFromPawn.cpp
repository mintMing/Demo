// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter/Service/CalculateDistanceFromPawn.h"

#include "AICharacter/SamuraiController.h"
#include "AICharacter/Samurai.h"
#include "Character/Character_Base.h"
#include "BehaviorTree/BlackboardComponent.h"

void UCalculateDistanceFromPawn::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	ASamuraiController *AIController = Cast<ASamuraiController>(OwnerComp.GetAIOwner());
	check(AIController);

	ASamurai *AISamurai = Cast<ASamurai>(AIController->GetPawn());
	check(AISamurai);

	ACharacter_Base *PlayerPawn = Cast<ACharacter_Base>(AISamurai->TargetPawn);
	check(PlayerPawn);

	float Distance = AISamurai->GetDistanceTo(PlayerPawn);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Distance : %f"), Distance));
	if (Distance < 250.0f)
	{
		AIController->GetBlackboardComponent()->SetValueAsBool("IsAttack", true);
	}
	else
	{
		if (Distance > 1000.0f)
		{
			AIController->GetBlackboardComponent()->SetValueAsBool("IsRun", true);
		}
		AIController->GetBlackboardComponent()->SetValueAsBool("IsAttack", false);
	}
}