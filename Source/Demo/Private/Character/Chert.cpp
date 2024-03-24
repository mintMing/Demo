// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Chert.h"

#include "GroomComponent.h"
#include "NiagaraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/PlayerController.h"
#include "Controller/DefaultPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h" // GetCharacterMovement

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
		if (IA_ChargeAttack)
		{
			EnhancedInputComponent->BindAction(IA_ChargeAttack, ETriggerEvent::Triggered, this, &AChert::ChargeAttack);
		}
		if (IA_Roll)
		{
			EnhancedInputComponent->BindAction(IA_Roll, ETriggerEvent::Started, this, &AChert::Roll);
		}/*
		if (IA_Slide)
		{
			EnhancedInputComponent->BindAction(IA_Slide, ETriggerEvent::Started, this, &AChert::Slide);
		}
		*/
		if (IA_ChangeWeapon)
		{
			EnhancedInputComponent->BindAction(IA_ChangeWeapon, ETriggerEvent::Started, this, &AChert::ChangeWeapons);
		}
		if (IA_Defense)
		{
			EnhancedInputComponent->BindAction(IA_Defense, ETriggerEvent::Triggered, this, &AChert::SwordDefense);
			EnhancedInputComponent->BindAction(IA_Defense, ETriggerEvent::Completed, this, &AChert::StopDefense);
		}
		/*
		if (IA_GameSet)
		{
			EnhancedInputComponent->BindAction(IA_GameSet, ETriggerEvent::Started, this, &AChert::OpenGameSet);
		}
		*/
	}
}

void AChert::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Stamina < 100.f && (CharacterState == ECharacterState::WALK || CharacterState != ECharacterState::IDLE))
	{
		Stamina += DeltaTime * StaminaRecoveryCoefficient;
	}
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
		CameraShakeFeedback();
		Stamina -= MeleeCombatSubStamina;
		SequenceAttackAnims(MeleeCombatAnims);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MeleeCombatAttack is cannot"));
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
		CharacterState = ECharacterState::ATTACK;
		Stamina -= SwordAttackSubStamina;
		CameraShakeFeedback();
		SequenceAttackAnims(SwordAttackAnims);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("SwordAttack is cannot"));
	}
}

bool AChert::IsCanSwordAttack()
{
	if ((CharacterState == ECharacterState::IDLE || CharacterState == ECharacterState::WALK) && Stamina >= SwordAttackSubStamina)
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

void AChert::Roll()
{
	switch (WeaponType)
	{
	case EWeaponType::MELEE:
		MeleeCombatRoll();
		break;
	case EWeaponType::SWORD:
		SwordRoll();
		break;
	}
}

void AChert::MeleeCombatRoll()
{
	if (IsCanMeleeCombatRoll())
	{
		CharacterState = ECharacterState::ROLLING;
		CameraShakeFeedback();
		Stamina -= MeleeCombatRollSubStamina;
		DirectionAnims(MeleeCombatRollAnims);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MeleeCombatRoll is cannot"));
	}
}

bool AChert::IsCanMeleeCombatRoll()
{
	if (CharacterState == ECharacterState::IDLE && Stamina >= MeleeCombatRollSubStamina)
	{
		return true;
	}
	else if (Stamina < MeleeCombatRollSubStamina)
	{
		ExhaustedStaminaPrompt();
		return false;
	}
	return false;
}

void AChert::SwordRoll()
{
	if (IsCanSwordRoll())
	{
		CharacterState = ECharacterState::ROLLING;
		Stamina -= SwordRollSubStamina;
		CameraShakeFeedback();
		DirectionAnims(SwordRollAnims);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("SwordRoll is cannot"));
	}
}

bool AChert::IsCanSwordRoll()
{
	if (CharacterState == ECharacterState::IDLE && Stamina >= SwordRollSubStamina)
	{
		return true;
	}
	else if (Stamina < SwordRollSubStamina)
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
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ChangeWeapons is cannot"));
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

void AChert::ChargeAttack()
{
	if (IsCanSwordAttack())
	{
		CharacterState = ECharacterState::ATTACK;
		Stamina -= SwordAttackSubStamina * 0.25;
		CameraShakeFeedback();
		UAnimInstance *CurAnimIns = GetMesh()->GetAnimInstance();
		if (CurAnimIns)
		{
			CurAnimIns->Montage_Play(SwordChargeAttackAnim[0]);
		}
	}
}

bool AChert::IsCanChargeAttack()
{
	if (IsCanSwordAttack() && WeaponType == EWeaponType::SWORD)
	{
		return true;
	}
	return false;
}

void AChert::Slide()
{
	CameraShakeFeedback();
	Stamina -= SlideSubStamina;
	CharacterState = ECharacterState::SLIDE;
	DirectionAnims(SlideAnims);
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