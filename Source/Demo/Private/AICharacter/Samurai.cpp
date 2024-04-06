// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter/Samurai.h"

#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "AICharacter/SamuraiController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Chert.h"
#include "Character/Character_Base.h"
#include "random"
#include "Enum/DamageLevel.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASamurai::ASamurai()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	Weapon->SetupAttachment(GetMesh(), "SWORD");
	
	HitColl = CreateDefaultSubobject<UBoxComponent>(TEXT("SwordCollision"));
	HitColl->SetupAttachment(Weapon);
	HitColl->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	HitColl->SetCollisionResponseToChannels(ECR_Ignore);
	HitColl->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	bIsEquip = false;
	MaxHitPoint = 100.f;
	HitPoint = MaxHitPoint;
	TargetPawn = nullptr;
	bIsAttack = false;
	bIsRoll = false;
	bIsAffected = false;
	bIsRun = false;
	bIsIgnoreHit = false;
	bIsDie = false;

	DamageLevel = EDamageLevel::COMMON;

	AIController = nullptr;

	LastAttackAnimsIndex = 0;

	SwordSphereCollisionRadius = 70.0f;

}

// Called when the game starts or when spawned
void ASamurai::BeginPlay()
{
	Super::BeginPlay();
	
	AIController = Cast<ASamuraiController>(GetController());
	if (IsValid(AIController))
	{
		checkf(AIController, TEXT("Samurai：AIController is not valid."));
	}

	FindTargetPawn();

}

// Called every frame
void ASamurai::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASamurai::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ASamurai::RandomPlayMontage(TArray<UAnimMontage *> Animaitons)
{
	int32 AttackAnimaIndex = UKismetMathLibrary::RandomIntegerInRange(0, Animaitons.Num() - 1);

	if (UAnimInstance *CurAnimIns = GetMesh()->GetAnimInstance())
	{
		if (AttackAnimaIndex != LastAttackAnimsIndex)
		{
			LastAttackAnimsIndex = AttackAnimaIndex;
			CurAnimIns->Montage_Play(Animaitons[AttackAnimaIndex]);
		}
		else
		{
			if (AttackAnimaIndex == 0)
			{
				int32 AddIndexNum = UKismetMathLibrary::RandomIntegerInRange(0, Animaitons.Num() - 2);
				AttackAnimaIndex += AddIndexNum;
				LastAttackAnimsIndex = AttackAnimaIndex;
				CurAnimIns->Montage_Play(Animaitons[AttackAnimaIndex]);
			}
			else
			{
				AttackAnimaIndex--;
				LastAttackAnimsIndex = AttackAnimaIndex;
				CurAnimIns->Montage_Play(Animaitons[AttackAnimaIndex]);
			}
		}
	}
}

void ASamurai::EnableAttackCollision()
{
	FVector SpherePos = GetActorLocation() + (GetActorForwardVector() * 70.0f);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;

	// pawn
	ObjectType.Add(EObjectTypeQuery::ObjectTypeQuery3);

	// 碰撞忽略
	TArray<AActor *> IgnoreActors;
	IgnoreActors.Add(this);

	// 碰撞目标
	TArray<AActor *> OverlapActors;

	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), SpherePos, SwordSphereCollisionRadius, ObjectType, nullptr, IgnoreActors, OverlapActors);

	if (OverlapActors.IsEmpty())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("nullptr"));
	}

	for (auto CollisionTarget : OverlapActors)
	{
		ACharacter_Base *Target = Cast<ACharacter_Base>(CollisionTarget);
		if (IsValid(Target))
		{
			checkf(Target, TEXT("Samurai：Target is not valid."));
		}

		if (Target)
		{
			Target->Affected();
		}
	}
}

void ASamurai::AccumulatedHit()
{
	AttackedCount++;

	if (AttackedCount == 1)
	{
		GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &ASamurai::ResetAttackCount, 3.0f, false);
	}
}

void ASamurai::ResetAttackCount()
{
	if (AttackedCount < 3)
	{
		AttackedCount = 0;
	}
	else
	{
		// 否则应用 BLEEDING 伤害
		DamageLevel = EDamageLevel::BLEEDING;
		ApplyBleedingDamage();
		AttackedCount = 0;
	}
}

void ASamurai::ApplyBleedingDamage()
{
	// 定义随机数生成器
	std::random_device rd; // 用于获得种子
	std::mt19937 gen(rd()); // Mersenne Twister 随机数引擎
	std::uniform_int_distribution<int> distribution(static_cast<int>(EDamageLevel::COMMON), static_cast<int>(EDamageLevel::COMMON) * 3); // 均匀分布，范围为 COMMON 到 BLEEDING 的三倍

	// 生成随机伤害值
	int damage = distribution(gen);

	// 确保伤害值不小于 COMMON 且不大于 BLEEDING 的三倍
	damage = FMath::Clamp(damage, static_cast<int>(EDamageLevel::COMMON), static_cast<int>(EDamageLevel::COMMON) * 3);

	PlayAffectedSound();
	HitPoint -= damage;

	DamageLevel = EDamageLevel::COMMON;
}

void ASamurai::Affected()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("NPC"));
	if (IsCanAffected())
	{
		DamageLevel = EDamageLevel::COMMON;
		bIsAffected = true;
		bIsAttack = false;
		RandomPlayMontage(AffectedAnims);
		if (HitPoint <= 5)
		{
			HitPoint -= 5;
			PlayAffectedSound();
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("NPC Die"));
			// Die();
		}
		else
		{
			HitPoint -= static_cast<int>(DamageLevel);
			AccumulatedHit();
		}
	}
}

bool ASamurai::IsCanAffected()
{
	if (!bIsIgnoreHit)
	{
		return true;
	}
	return false;
}

void ASamurai::Attack()
{
	if (IsCanAttack())
	{
		bIsAttack = true;
		RandomPlayMontage(AttackAnims);
	}
}

bool ASamurai::IsCanAttack()
{
	return bIsEquip && !bIsAttack && !bIsAffected && !bIsRoll;
}

void ASamurai::FindTargetPawn()
{
	while (TargetPawn == nullptr)
	{
		AActor *FindActor = UGameplayStatics::GetActorOfClass(GetWorld(), InsPawn);
		if (FindActor)
		{
			TargetPawn = Cast<ACharacter_Base>(FindActor);
			if (IsValid(TargetPawn))
			{
				checkf(TargetPawn, TEXT("Samurai：TargetPawn is not valid."));
			}
		}
	}
	if (TargetPawn)
	{
		AIController->GetBlackboardComponent()->SetValueAsObject("TarPawn", TargetPawn);
	}
}

void ASamurai::RunningMovement(bool IsRun)
{

}

void ASamurai::DrawTheSword()
{
	bIsEquip = true;
	UAnimInstance *CurAnimIns = GetMesh()->GetAnimInstance();
	if (CurAnimIns)
	{
		CurAnimIns->Montage_Play(EquipAnim[0]);
		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "WEAPON_R");
		if (AIController)
		{
			AIController->GetBlackboardComponent()->SetValueAsBool("IsEquip", bIsEquip);
		}
	}
}