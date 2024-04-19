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
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"


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
	bIsDeath = false;

	DamageLevel = EDamageLevel::COMMON;

	AIController = nullptr;

	LastAttackAnimsIndex = 0;

	SwordSphereCollisionRadius = 70.0f;

	RushAttackPosition = FVector(0, 0, 0);
	ThumpDirection = 1;

	MaxHitPoint = 100.0f;
	HitPoint = MaxHitPoint;

}

// Called when the game starts or when spawned
void ASamurai::BeginPlay()
{
	Super::BeginPlay();

	// 关闭tick
	SetActorTickEnabled(false);
	
	AIController = Cast<ASamuraiController>(GetController());
	check(AIController);

	GetWorld()->GetTimerManager().SetTimer(DelayFindPlayerPtr, this, &ASamurai::FindTargetPawn, 1.0f, false, 1.0f);
	GetWorld()->GetTimerManager().SetTimer(DelayRandomThumb, this, &ASamurai::EnableThump,
		UKismetMathLibrary::RandomFloatInRange(13.f, 19.f), true, UKismetMathLibrary::RandomFloatInRange(13.f, 19.f));
}

// Called every frame
void ASamurai::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ThumpMovement(ThumpDirection);
}

// Called to bind functionality to input
void ASamurai::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void ASamurai::RandomPlayMontage(TArray<UAnimMontage *> Animaitons)
{
	int32 AttackAnimaIndex = UKismetMathLibrary::RandomIntegerInRange(0, Animaitons.Num() - 1);

	UAnimInstance *CurAnimIns = GetMesh()->GetAnimInstance();
	
	if (IsValidChecked(CurAnimIns))
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
		checkf(Target, TEXT("Samurai：Target is not valid."));

		if (Target)
		{
			Target->Affected();
		}
	}
}

FVector ASamurai::GetTargetPosition()
{
	return TargetPawn->DirectionArrow->GetComponentLocation();
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
	std::uniform_int_distribution<int> distribution(static_cast<int>(EDamageLevel::COMMON), static_cast<int>(EDamageLevel::COMMON) * 1.1); // 均匀分布，范围为 COMMON 到 BLEEDING 的倍数

	// 生成随机伤害值
	int damage = distribution(gen);

	// 确保伤害值不小于 COMMON 且不大于 BLEEDING 的三倍
	damage = FMath::Clamp(damage, static_cast<int>(EDamageLevel::COMMON), static_cast<int>(EDamageLevel::COMMON) * 1.2);

	PlayAffectedSound();
	HitPoint -= damage;

	DamageLevel = EDamageLevel::COMMON;
}

void ASamurai::Affected()
{
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
			Death();
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
		bool RandomAttackBool = UKismetMathLibrary::RandomBoolWithWeight(0.9);

		if (RandomAttackBool)
		{
			bIsAttack = true;
			AIController->GetBlackboardComponent()->SetValueAsBool("IsRun", false);
			RunMovement(false);
			RandomPlayMontage(AttackAnims);
		}
		else
		{
			Roll();
		}

	}
}

bool ASamurai::IsCanAttack()
{
	return bIsEquip && !bIsAttack && !bIsAffected && !bIsRoll;
}

void ASamurai::Roll()
{
	UAnimInstance *CurAnimIns = GetMesh()->GetAnimInstance();

	if (IsValidChecked(CurAnimIns))
	{
		bIsAttack = false;
		bIsAffected = false;
		bIsIgnoreHit = true;
		bIsRoll = true; 
		int32 RollIndex = UKismetMathLibrary::RandomIntegerInRange(0, 3);
		CurAnimIns->Montage_Play(RollingAnims[RollIndex]);
	}
}

void ASamurai::Death()
{
	bIsDeath = true;
	AIController->GetBlackboardComponent()->SetValueAsBool("IsAnyoneDie", true);

	//关闭胶囊体的碰撞
	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
		
	if (GetMesh())
	{
		GetMesh()->SetCollisionObjectType(ECC_PhysicsBody);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		GetMesh()->SetCollisionResponseToAllChannels(ECR_Block);
		GetMesh()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

		GetMesh()->SetAllBodiesBelowSimulatePhysics("pelvis", true);
	}
	DeathUI();
}

void ASamurai::DeathUI()
{

}

void ASamurai::RushThump()
{
	if (IsCanRushThump())
	{
		if (UAnimInstance *CurAnimIns = GetMesh()->GetAnimInstance())
		{
			bIsAttack = true;
			AIController->GetBlackboardComponent()->SetValueAsBool("IsRun", false);
			RushAttackPosition = GetTargetPosition();
			RunMovement(false);
			CurAnimIns->Montage_Play(RushAttackAnim[0]);
		}
	}
}

bool ASamurai::IsCanRushThump()
{
	return bIsEquip;
}

void ASamurai::EnableThump()
{
	if (bIsEquip)
	{
		AIController->GetBlackboardComponent()->SetValueAsBool("IsThump", true);

		RunMovement(false);

		if (UKismetMathLibrary::RandomBool())
		{
			ThumpDirection = 1;
		}
		else
		{
			ThumpDirection = -1;
		}
	}
}

void ASamurai::ThumpMovement(int32 Direction)
{
	const FRotator LocalRotation = GetActorRotation();

	// 由 FRotator 创建一个旋转矩阵，将局部空间转换为世界空间，从旋转矩阵中获取单位 Y 轴向量。
	const FVector LocalVector = FRotationMatrix(FRotator(0, LocalRotation.Yaw, 0)).GetUnitAxis(EAxis::Y);
	AddMovementInput(LocalVector, Direction);
}

void ASamurai::RushThumpDistance(float Lerp)
{
	FVector LerpLoc = UKismetMathLibrary::VLerp(GetActorLocation(), RushAttackPosition, Lerp);
	SetActorLocation(FVector(LerpLoc.X, LerpLoc.Y, GetActorLocation().Z));
}

void ASamurai::FindTargetPawn()
{
	while (TargetPawn == nullptr)
	{
		AActor *FindActor = UGameplayStatics::GetActorOfClass(GetWorld(), InsPawn);
		if (IsValidChecked(FindActor))
		{
			TargetPawn = Cast<ACharacter_Base>(FindActor);
			
		}
	}
	checkf(TargetPawn, TEXT("Samurai：TargetPawn is not valid."));
	AIController->GetBlackboardComponent()->SetValueAsObject("TarPawn", TargetPawn);
}

void ASamurai::RunMovement(bool IsRun)
{
	if (IsRun)
	{
		GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	}
}

void ASamurai::DrawTheSword()
{
	if (!bIsEquip)
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

}