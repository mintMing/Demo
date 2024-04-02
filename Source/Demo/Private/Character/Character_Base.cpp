// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Character_Base.h"


#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h" // GetCharacterMovement
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "Controller/DefaultPlayerController.h"

#include "Components/AudioComponent.h"
#include "Components/ArrowComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "AICharacter/AISamurai.h"

// Sets default values
ACharacter_Base::ACharacter_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);

	DirectionArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	DirectionArrow->SetupAttachment(RootComponent);

	GetCharacterMovement()->MaxWalkSpeed = 200.0f;

	CharacterState = ECharacterState::IDLE;
	WeaponType = EWeaponType::MELEE;

	MaxHitPoint = 100.0f;
	HitPoint = MaxHitPoint;
	MaxStamina = 100.0f;
	Stamina = MaxStamina;

	bIsRun = false;
	bIsEquip = false;
	bIgnoreHit = false;

	LastMeleeIndex = 0;
	LastSwordIndex = 0;
	SequenceAttackAnimIndex = 0;
	CharacterDirection = FVector(0.0f, 0.0f, 0.0f);

	StaminaRecoveryCoefficient = 20.0f;
	MeleeCombatSubStamina = 20.0f;
	MeleeCombatRollSubStamina = 20.0f;
	SwordRollSubStamina = 20.0f;
	SwordAttackSubStamina = 20.0f;
	SlideSubStamina = 10.0f;

	MoveForwardVal = 0.0f;
	MoveRightVal = 0.0f;

	AICharacterTarget = nullptr;

	MeleeSphereCollisionRadius = 35.0f;


}

// Called when the game starts or when spawned
void ACharacter_Base::BeginPlay()
{
	Super::BeginPlay();
	
	/*
	if (InsAICharacterTarget == nullptr)
	{
		FindAICharacterPtr();
	}
	*/

	FindAICharacterPtr();
	
}

// Called every frame
void ACharacter_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	//if (CharacterState == ECharacterState::IDLE && GetVelocity().Size() < 5.0f)
	//{
		ForwardVec = (MoveForwardVal * UKismetMathLibrary::GetForwardVector(FRotator(0, GetController()->GetControlRotation().Yaw, 0)) * 200.0f);
		RightVec = (MoveRightVal * UKismetMathLibrary::GetRightVector(FRotator(0, GetController()->GetControlRotation().Yaw, 0)) * 200.0f);
		CharacterDirection = GetActorLocation() + ForwardVec + RightVec;

		//FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), ((CharacterDirection - GetActorLocation()).GetSafeNormal()).Rotation(), GetWorld()->GetDeltaSeconds(), CharacterTurnInterpSpeed);
		//SetActorRotation(NewRotation);
	//}
	UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), CharacterDirection, 300.0f, FColor::Red);
	
	
}

// Called to bind functionality to input
void ACharacter_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacter_Base::Move(const FInputActionValue &Val)
{
	auto *PC = GetController();

	// 获取移动向量
	FVector2D MoveVec = Val.Get<FVector2D>();

	MoveForwardVal = MoveVec.Y;
	MoveRightVal = MoveVec.X;

	MoveAxis = MoveVec;


	if (PC != nullptr)
	{
		// 获取 Yaw ,即水平旋转角度
		const FRotator ChertRotator = PC->GetControlRotation();
		const FRotator YawRotation(0, ChertRotator.Yaw, 0);

		// 获取向前向量
		const FVector MoveDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		//获取向右向量
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(MoveDir, MoveVec.Y);
		AddMovementInput(RightDirection, MoveVec.X);
	}
}

void ACharacter_Base::MoveEnd()
{
	MoveAxis = FVector2D(0, 0);
}

void ACharacter_Base::Look(const FInputActionValue &Val)
{
	auto *PC = GetController();

	FVector2D LookAxisVec = Val.Get<FVector2D>();

	if (PC != nullptr)
	{
		AddControllerYawInput(LookAxisVec.X);
		AddControllerPitchInput(LookAxisVec.Y);
	}
}

void ACharacter_Base::StartRunning()
{
	if (IsCanRun())
	{
		bIsRun = true;
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
}

void ACharacter_Base::StopRunning()
{
	bIsRun = false;
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;
}

bool ACharacter_Base::IsCanRun()
{
	if (CharacterState == ECharacterState::IDLE || CharacterState == ECharacterState::WALK)
	{
		return true;
	}
	return false;
}

void ACharacter_Base::RandomAttackAnims(TArray<UAnimMontage *> NeedRandomAnims, int32 &LastAttackAnimsIndex)
{
	// 随机选择近战攻击动画
	int32 AttackAnimIndex = UKismetMathLibrary::RandomIntegerInRange(0, NeedRandomAnims.Num() - 1);

	// 获取当前动画实例
	UAnimInstance *CurAnimIns = GetMesh()->GetAnimInstance();

	if (CurAnimIns)
	{
		// 当前动画不等于上文动画索引时，播放动画
		if (AttackAnimIndex != LastAttackAnimsIndex)
		{
			LastAttackAnimsIndex = AttackAnimIndex;
			CurAnimIns->Montage_Play(NeedRandomAnims[AttackAnimIndex]);
		}
		else
		{
			if (AttackAnimIndex == 0)
			{
				uint32 AddIndexNum = UKismetMathLibrary::RandomIntegerInRange(0, NeedRandomAnims.Num() - 1);
				AttackAnimIndex = +AddIndexNum;
				LastAttackAnimsIndex = AddIndexNum;
				CurAnimIns->Montage_Play(NeedRandomAnims[AttackAnimIndex]);
			}
			else
			{
				AttackAnimIndex--;
				LastAttackAnimsIndex = AttackAnimIndex;
				CurAnimIns->Montage_Play(NeedRandomAnims[AttackAnimIndex]);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("RandomAttackAnim : CurAnimIns is nullptr"));
	}
}

void ACharacter_Base::SequenceAttackAnims(TArray<UAnimMontage *> NeedRandomAnims)
{
	UAnimInstance *CurAnimIns = GetMesh()->GetAnimInstance();

	if (CurAnimIns)
	{
		CurAnimIns->Montage_Play(NeedRandomAnims[SequenceAttackAnimIndex]);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SequenceAttackAnims : CurAnimIns is nullptr"));
	}
}

void ACharacter_Base::DirectionAnims(TArray<UAnimMontage *> DirectionAnims)
{
	UAnimInstance *CurAnimIns = GetMesh()->GetAnimInstance();

	if (CurAnimIns)
	{
		if(GetVelocity().Size() < 1.0f)
		{
			CurAnimIns->Montage_Play(DirectionAnims[4]);
			return;
		}
		else
		{
			if (MoveForwardVal == 1)
			{
				CurAnimIns->Montage_Play(DirectionAnims[0]);
			}
			else if (MoveForwardVal == -1)
			{
				CurAnimIns->Montage_Play(DirectionAnims[1]);
			}
			else if (MoveRightVal == 1)
			{
				CurAnimIns->Montage_Play(DirectionAnims[2]);
			}
			else if (MoveRightVal == -1)
			{
				CurAnimIns->Montage_Play(DirectionAnims[3]);
			}
			else
			{
				CurAnimIns->Montage_Play(DirectionAnims[0]);
			}
		}

	}
}

void ACharacter_Base::EnableMeleeCollision()
{
	FVector SpherePos = GetActorLocation() + (GetActorForwardVector() * 35.0f);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;

	// pawn
	ObjectType.Add(EObjectTypeQuery::ObjectTypeQuery3);

	// 碰撞忽略
	TArray<AActor *> IgnoreActors;
	IgnoreActors.Add(this);

	// 碰撞目标
	TArray<AActor *> OverlapActors;

	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), SpherePos, MeleeSphereCollisionRadius, ObjectType, nullptr, IgnoreActors, OverlapActors);

	for (auto CollisionTarget : OverlapActors)
	{
		if (AAISamurai *Target = Cast<AAISamurai>(CollisionTarget))
		{
			//Target->Affected();
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("打到了"));
		}
	}
}

void ACharacter_Base::FindAICharacterPtr()
{
	AICharacterTarget = Cast<AAISamurai>(UGameplayStatics::GetActorOfClass(GetWorld(), InsAICharacterTarget));

	if (AICharacterTarget == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Character_Base：FindAICharacterPtr of AICharacterTarget is nullptr"));
	}
}
