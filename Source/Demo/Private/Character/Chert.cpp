// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Chert.h"

#include "Combo/ComboGuide.h"
#include "Controller/DefaultPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h" // GetCharacterMovement
#include "GameFramework/PlayerController.h"
#include "GroomComponent.h"
#include "MotionWarpingComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AICharacter/LockSystem.h"
#include "Kismet\KismetMathLibrary.h"


AChert::AChert()
{
	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("GroomComponent1"));
	Brows = CreateDefaultSubobject<UGroomComponent>(TEXT("GroomComponent2"));
	
	Hair->SetupAttachment(GetMesh(), "head1Socket");
	Brows->SetupAttachment(Hair);

	Scabbard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMComponent"));
	Scabbard->SetupAttachment(GetMesh(), "SCABBARD");

	Sword = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkMeshComponent"));
	Sword->SetupAttachment(GetMesh(), "SWORD");

	SwordScar = CreateDefaultSubobject<UNiagaraComponent>(TEXT("SwordScar"));
	SwordScar->SetupAttachment(Sword);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	ComboGuide = CreateDefaultSubobject<UComboGuide>(TEXT("ComboGuide"));

	//bIsUseDynamicCamera = true;

}

void AChert::BeginPlay()
{
	Super::BeginPlay();

	// 获取玩家控制器
	ADefaultPlayerController *PC = Cast<ADefaultPlayerController>(GetController());

	if (PC)
	{
		// 增强输入子系统
		auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("UEnhancedInputComponent Subsystem is null"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ADefaultPlayerController is null"));
	}
}

void AChert::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 绑定输入
	auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		if (IA_Move)
		{
			EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AChert::Move);
		}
		if (IA_Look)
		{
			EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AChert::Look);
		}
		if (IA_Run)
		{
			EnhancedInputComponent->BindAction(IA_Run, ETriggerEvent::Started, this, &AChert::StartRunning);
			EnhancedInputComponent->BindAction(IA_Run, ETriggerEvent::Completed, this, &AChert::StopRunning);
		}
		if (IA_Attack)
		{
			EnhancedInputComponent->BindAction(IA_Attack, ETriggerEvent::Started, this, &AChert::AttackMode);
		}
		
		if (IA_Slide)
		{
			EnhancedInputComponent->BindAction(IA_Slide, ETriggerEvent::Started, this, &AChert::Slide);
		}
		
		if (IA_ChangeWeapon)
		{
			EnhancedInputComponent->BindAction(IA_ChangeWeapon, ETriggerEvent::Started, this, &AChert::ChangeWeapons);
		}
		if (IA_Defense)
		{
			EnhancedInputComponent->BindAction(IA_Defense, ETriggerEvent::Triggered, this, &AChert::SwordDefense);
			EnhancedInputComponent->BindAction(IA_Defense, ETriggerEvent::Completed, this, &AChert::StopDefense);
		}
		
		if (IA_GameSet)
		{
			//EnhancedInputComponent->BindAction(IA_GameSet, ETriggerEvent::Started, this, &AChert::OpenGameSet);
		}
		if (IA_LockPawn)
		{
			EnhancedInputComponent->BindAction(IA_GameSet, ETriggerEvent::Started, this, &AChert::LockAI);
		}
		
	}
}

void AChert::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Stamina < 100.f && (CharacterState == ECharacterState::WALK || CharacterState == ECharacterState::IDLE))
	{
		Stamina += DeltaTime * StaminaRecoveryCoefficient;
	}

	if (IsLock)
	{
		FVector TargetLocation = TargetActor->GetActorLocation();
		TargetLocation.Z -= 50.0f; // 向下移动 50 个单位

		FRotator Rot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);

		FRotator Rot01 = FMath::RInterpTo(GetControlRotation(), Rot, DeltaTime, 4.0f);

		GetController()->SetControlRotation(FRotator(Rot.Roll, Rot01.Yaw, Rot01.Pitch));


		
		//GetCharacterMovement()->bOrientRotationToMovement = false;
		//GetCharacterMovement()->bUseControllerDesiredRotation = true;
	}
	/*
	else
	{
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
	}
	*/
}

void AChert::AttackMode()
{
	switch (WeaponType)
	{
	case EWeaponType::MELEE:
		MeleeCombatAttack();
		break;
	case EWeaponType::SWORD:
		SwordAttack();
		break;
	}
}

void AChert::MeleeCombatAttack()
{
	if (IsCanMeleeCombatAttack())
	{
		CharacterState = ECharacterState::ATTACK;
		CameraShakeFeedback(true);
		Stamina -= MeleeCombatSubStamina;
		SequenceAttackAnims(MeleeCombatAnims);
	}
}

bool AChert::IsCanMeleeCombatAttack()
{
	if ((CharacterState == ECharacterState::IDLE || CharacterState == ECharacterState::WALK || CharacterState == ECharacterState::RUN) && Stamina >= MeleeCombatSubStamina)
	{
		return true;
	}
	else if (Stamina < MeleeCombatSubStamina)
	{
		ExhaustedStaminaPrompt();
		return false;
	}
	return false;
}

void AChert::SwordAttack()
{
	if (IsCanSwordAttack())
	{
		Stamina -= SwordAttackSubStamina;
		CameraShakeFeedback(false);
		ComboGuide->Pre();
	}
}

bool AChert::IsCanSwordAttack()
{
	if ((CharacterState == ECharacterState::IDLE || CharacterState == ECharacterState::WALK) && 
		Stamina >= SwordAttackSubStamina)
	{
		return true;
	}
	else if (Stamina < SwordAttackSubStamina)
	{
		ExhaustedStaminaPrompt();
		return false;
	}
	return false;
}

void AChert::ChangeWeapons()
{
	if (IsCanChangeWeapon())
	{
		if (WeaponType == EWeaponType::MELEE)
		{
			bIsEquip = true;
			WeaponType = EWeaponType::SWORD;
			Sword->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "r_weapon_socket");
		}
		else if (WeaponType == EWeaponType::SWORD)
		{
			bIsEquip = false;
			WeaponType = EWeaponType::MELEE;
			Sword->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "SWORD");
		}
	}
}

bool AChert::IsCanChangeWeapon()
{
	if (CharacterState == ECharacterState::IDLE || CharacterState == ECharacterState::WALK)
	{
		return true;
	}
	return false;
}

void AChert::SwordDefense()
{
	if (IsCanSwordDefense())
	{
		CharacterState = ECharacterState::DEFENSE;
	}
}

bool AChert::IsCanSwordDefense()
{
	if ((CharacterState == ECharacterState::IDLE || CharacterState == ECharacterState::WALK) && WeaponType == EWeaponType::SWORD)
	{
		return true;
	}
	return false;
}

void AChert::StopDefense()
{
	if (GetVelocity().Size() > 1.0f)
	{
		CharacterState = ECharacterState::WALK;
	}
	else
	{
		if (GetVelocity().Size() == 0)
		{
			CharacterState = ECharacterState::IDLE;
		}
	}
	CharacterState = ECharacterState::IDLE;
}

void AChert::Slide()
{
	if (IsCanSlide())
	{
		CameraShakeFeedback(false);
		Stamina -= SlideSubStamina;
		CharacterState = ECharacterState::SLIDE;
		DirectionAnims(SlideAnims);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("DD"));
	}

}

bool AChert::IsCanSlide()
{
	if ((CharacterState == ECharacterState::IDLE || CharacterState == ECharacterState::WALK) && Stamina >= SlideSubStamina)
	{
		return true;
	}
	else if (Stamina < SlideSubStamina)
	{
		ExhaustedStaminaPrompt();
		return false;
	}
	return false;
}

void AChert::Affected()
{
	if (IsCanAffected())
	{
		if (CharacterState == ECharacterState::DEFENSE)
		{
			if (Stamina < DefenseSubStamina)
			{
				DestroyDefense();
			}
			else
			{
				CameraShakeFeedback(false);
				RandomPlayAnims(SwordDefenseAnims);
				Stamina -= DefenseSubStamina;
			}
		}
		else
		{
			CameraShakeFeedback(true);
			int damageVal = DamageCalculation(BaseDamage, StaminaModifier, HitPointModifier);
			if (HitPoint <= damageVal)
			{
				HitPoint -= damageVal;
				HitPoint = 0;
			}
			else
			{
				HitPoint -= damageVal;
			}
		}
	}
}

bool AChert::IsCanAffected()
{
	return true;
	/*
	if (!bIsIgnoreHit)
	{
		return true;
	}
	return false;
	*/
}

void AChert::DestroyDefense()
{
	CharacterState = ECharacterState::AFFECTED;

	CameraShakeFeedback(true);

	if (UAnimInstance *CurAnimIns = GetMesh()->GetAnimInstance())
	{
		CurAnimIns->Montage_Play(DestroyDefenseAnims[0]);
	}
	Stamina -= DefenseSubStamina;
	if (Stamina < 0)
	{
		Stamina = 0;
	}
}

void AChert::GetClosestAI(float Radius, AActor *&Target, bool &CollisionAnyItem)
{
	/*
	LockActors.Empty();

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;
	ObjectType.Add(EObjectTypeQuery::ObjectTypeQuery3);

	TArray<AActor *> IgnoreActors;
	IgnoreActors.Add(this);

	TArray<FHitResult> OutHits;

	CollisionAnyItem = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), GetActorLocation(), GetActorLocation(),
		Radius, ObjectType, false, IgnoreActors, EDrawDebugTrace::ForDuration,
		OutHits, true);

	for (const FHitResult& Elem : OutHits)
	{
		AActor *HitActor = Elem.GetActor();
		if (HitActor->GetClass()->ImplementsInterface(ULockSystem::StaticClass()))
		{
			LockActors.Add(HitActor);
		}
	}

	if (LockActors.Num() > 0)
	{
		Target = LockActors[0];
		DistanceofPlayerAndAI = FMath::Abs(Target->GetDistanceTo(this));
	}

	for (const AActor *Elem : LockActors)
	{
		if (Elem->GetDistanceTo(this) < DistanceofPlayerAndAI)
		{
			Elem = Target;
		}
	}
	*/
}

void AChert::LockAI()
{
	if (IsLock)
	{
		IsLock = false;
	}
	else
	{
		GetClosestAI(500, TargetActor, IsCollisionAnyItem);
		if (IsCollisionAnyItem)
		{
			IsLock = true;
		}
		else
		{
			IsLock = false;
		}
	}
}


/*
void AChert::SetDynamicCamera(bool UseDynamicCamera)
{
	this->bIsUseDynamicCamera = UseDynamicCamera;
}

void AChert::GetDCProperty(FTransform &PivotTransform, double &FOV, bool &bIsRight)
{
	PivotTransform = FTransform();
	FOV = 0.0f;
	bIsRight = false;
}
*/
