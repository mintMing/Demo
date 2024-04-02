// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter/AISamurai.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "AICharacter/SamuraiAiController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Character/Character_Base.h"

AAISamurai::AAISamurai()
{

	Sword = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EnemySword"));
	Sword->SetupAttachment(GetMesh(), "SWORD");

	HitColl = CreateDefaultSubobject<UBoxComponent>(TEXT("SwordCollision"));
	HitColl->SetupAttachment(Sword);
	HitColl->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	HitColl->SetCollisionResponseToChannels(ECR_Ignore);
	HitColl->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	bEquip = false;
	MaxHitPoint = 100.f;
	HitPoint = MaxHitPoint;
	TargetPawn = nullptr;
	bAttack = false;
	bRolling = false;
	bInjury = false;
	bRunning = false;
	bIgnoreHit = false;
	bDie = false;

	AIController = nullptr;

}

void AAISamurai::BeginPlay()
{
	Super::BeginPlay();

	AIController = Cast<ASamuraiAiController>(GetController());
	FindTargetPawn();

}

float AAISamurai::GetAICharacterHP()
{
	return 0.0f;
}

float AAISamurai::GetAICharacterMaxHP()
{
	return 0.0f;
}

void AAISamurai::FindTargetPawn()
{
	while (TargetPawn == nullptr)
	{
		AActor *FindActor = UGameplayStatics::GetActorOfClass(GetWorld(), InsPawn);
		if (FindActor)
		{
			TargetPawn = Cast<ACharacter_Base>(FindActor);
		}
	}
	if (TargetPawn)
	{
		AIController->GetBlackboardComponent()->SetValueAsObject("TargetPawn", TargetPawn);
	}
}

void AAISamurai::RunningMovement(bool IsRun)
{
}

void AAISamurai::DrawTheSword()
{
	bEquip = true;
	if (UAnimInstance *CurAnimIns = GetMesh()->GetAnimInstance())
	{
		CurAnimIns->Montage_Play(EquipAnim[0]);
		Sword->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "WEAPON_R");
		if (AIController)
		{
			AIController->GetBlackboardComponent()->SetValueAsBool("IsEquip", bEquip);
		}
	}
}
