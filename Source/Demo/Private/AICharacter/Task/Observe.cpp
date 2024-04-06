// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter/Task/Observe.h"

//#include "AICharacter/SamuraiAiController.h"
#include "Character/Chert.h"

#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UObserve::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
	/*
	ASamuraiAiController *AIController = Cast<ASamuraiAiController>(OwnerComp.GetAIOwner());
	checkf(AIController, TEXT("Task：AIController的类型转换为nullptr。"));

	AChert *SourceMesh = Cast<AChert>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	checkf(AIController, TEXT("Task：TargetMesh的类型转换为nullptr。"));

	FVector TargetHeadLocation = SourceMesh->GetMesh()->GetBoneLocation(TEXT("head")); 
	UE_LOG(LogTemp, Warning, TEXT("Task: Player：X:%f Y:%f Z:%f"), TargetHeadLocation.X, TargetHeadLocation.Y, TargetHeadLocation.Z);

	FVector StartBoneLocation = AIController->GetCharacter()->GetMesh()->GetBoneLocation("head");
	UE_LOG(LogTemp, Warning, TEXT("Task: Samurai：X:%f Y:%f Z:%f"), StartBoneLocation.X, StartBoneLocation.Y, StartBoneLocation.Z);


	//FRotator RoatatorDirector = UKismetMathLibrary::FindLookAtRotation(SourceHeadLocation, TargetBoneLocation);

	FRotator RotatorToLook = UKismetMathLibrary::FindLookAtRotation(StartBoneLocation, TargetHeadLocation);
	AIController->GetCharacter()->GetMesh()->TransformBone();

	*/
	return EBTNodeResult::Succeeded;
}
