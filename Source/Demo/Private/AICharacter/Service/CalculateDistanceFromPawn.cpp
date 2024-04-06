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
	if (!IsValid(AIController))
	{
		UE_LOG(LogTemp, Error, TEXT("UCalculateDistanceFromPawn: AIController is nullptr."));
	}

	ASamurai *AISamurai = Cast<ASamurai>(AIController->GetPawn());
	if (!IsValid(AISamurai))
	{
		UE_LOG(LogTemp, Error, TEXT("UCalculateDistanceFromPawn: AISamurai is nullptr."));
	}

	ACharacter_Base *PlayerPawn = Cast<ACharacter_Base>(AISamurai->TargetPawn);
	if (!IsValid(PlayerPawn))
	{
		UE_LOG(LogTemp, Error, TEXT("UCalculateDistanceFromPawn: PlayerPawn is nullptr."));
	}

	float Distance = PlayerPawn->GetDistanceTo(PlayerPawn);
	if (Distance < 250.0f)
	{
		AIController->GetBlackboardComponent()->SetValueAsBool("IsAttack", true);
	}
	else if (Distance > 250.0f)
	{
		AIController->GetBlackboardComponent()->SetValueAsBool("IsRun", true);
	}
	AIController->GetBlackboardComponent()->SetValueAsBool("IsAttack", true);
	
}
