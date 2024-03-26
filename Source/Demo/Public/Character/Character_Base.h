// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Enum/CharacterState.h"
#include "Enum/WeaponType.h"

#include "Character_Base.generated.h"


class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
enum class EWeaponType : uint8;
enum class ECharacterState : uint8;
class UStaticMeshComponent;
class UArrowComponent;
struct FInputActionValue;


UCLASS()
class DEMO_API ACharacter_Base : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacter_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> DirectionArrow;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Action")
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Action")
	TObjectPtr<UInputAction> IA_Look;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Action")
	TObjectPtr<UInputAction> IA_Run;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Action")
	TObjectPtr<UInputAction> IA_Attack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Action")
	TObjectPtr<UInputAction> IA_ChargeAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Action")
	TObjectPtr<UInputAction> IA_Roll;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Action")
	TObjectPtr<UInputAction> IA_Slide;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Action")
	TObjectPtr<UInputAction> IA_ChangeWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Action")
	TObjectPtr<UInputAction> IA_Defense;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Action")
	TObjectPtr<UInputAction> IA_TurnBack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Action")
	TObjectPtr<UInputAction> IA_GameSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Action")
	UInputAction *AtkAction;


	// 状态属性
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute")
	bool bIsEquip;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute")
	bool bIsRun;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute")
	EWeaponType WeaponType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute")
	ECharacterState CharacterState;

	//生命值
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute")
	float HitPoint;

	// 最大生命值
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute")
	float MaxHitPoint;

	// 体力值
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute")
	float Stamina;

	// 最大体力值
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute")
	float MaxStamina;

	// 体力值回复系数
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute")
	float StaminaRecoveryCoefficient;

	// 不同状态的体力值衰减速度
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute")
	float MeleeCombatSubStamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute")
	float MeleeCombatRollSubStamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute")
	float SlideSubStamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute")
	float SwordAttackSubStamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute")
	float SwordRollSubStamina;



protected:
	void Move(const FInputActionValue &Val);

	void Look(const FInputActionValue &Val);

	void StartRunning();
	void StopRunning();
	bool IsCanRun(); 	// 限制防御时奔跑


	// 辅助方法
protected:

	// 随机播放攻击动画
	void RandomAttackAnims(TArray<UAnimMontage *> NeedRandomAnims, int32 &LastAttackAnimsIndex);
	int32 LastMeleeIndex; 
	int32 LastSwordIndex; 	

	// 按序播放攻击动画
	void SequenceAttackAnims(TArray<UAnimMontage *> NeedRandomAnims);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 SequenceAttackAnimIndex;  	// 顺序动画索引 动画蓝图迭代

	// 具有方向行的动画
	void DirectionAnims(TArray<UAnimMontage *> DirectionAnims);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector CharacterDirection; 	// 角色方向
	float MoveRightVal;
	float MoveForwardVal;
	FVector ForwardVec;
	FVector RightVec;

	// 体力不足提示
	UFUNCTION(BlueprintImplementableEvent)
	void ExhaustedStaminaPrompt();

	// 摄像机震动反馈
	UFUNCTION(BlueprintImplementableEvent)
	void CameraShakeFeedback();

	// 角色转向插值速度
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute")
	float CharacterTurnInterpSpeed;

	// 获取当前体力值
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetCurrentStamina() const { return Stamina; };

	// 获取当前最大体力值
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetMaxStamine() const { return MaxStamina; };

protected:

	virtual void AttackMode() PURE_VIRTUAL(APlayer_Base::AttackMode, );

	virtual void Roll() PURE_VIRTUAL(APlayer_Base::Roll, );

	virtual void Slide() PURE_VIRTUAL(APlayer_Base::Slide, );

	// 更换武器
	virtual void ChangeWeapons() PURE_VIRTUAL(APlayer_Base::ChangeWeapons, );

	// 持剑防御
	virtual void SwordDefense()  PURE_VIRTUAL(APlayer_Base::SwordDefense, );
	virtual void StopDefense()  PURE_VIRTUAL(APlayer_Base::StopDefense, );

	// 原地后退
	virtual void StepBackInPlace() PURE_VIRTUAL(APlayer_Base::StepBackInPlace, );



};
