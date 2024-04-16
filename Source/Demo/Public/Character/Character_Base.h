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

class ASamurai;


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
	TObjectPtr<UInputAction> IA_LockPawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Action")
	TObjectPtr<UInputAction> IA_GameSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Action")
	UInputAction *AtkAction;


	// ״̬����
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute")
	bool bIsEquip;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute")
	bool bIsRun;

	// �Ƿ�����ܻ�
	UPROPERTY(BlueprintReadWrite, Category = Attribute)
	bool bIsIgnoreHit;

	UPROPERTY(BlueprintReadWrite, Category = Attribute)
	bool bIsDeath;

	//����ֵ
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute")
	float HitPoint;

	// �������ֵ
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute")
	float MaxHitPoint;

	// ����ֵ
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute")
	float Stamina;

	// �������ֵ
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute")
	float MaxStamina;

	// ����ֵ�ظ�ϵ��
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute")
	float StaminaRecoveryCoefficient;

	// ��ͬ״̬������ֵ˥���ٶ�
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute")
	float DefenseSubStamina;


public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute")
	EWeaponType WeaponType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute")
	ECharacterState CharacterState;

protected:
	void Move(const FInputActionValue &Val);

	void Look(const FInputActionValue &Val);

	void StartRunning();
	void StopRunning();
	bool IsCanRun(); 	// ���Ʒ���ʱ����


	// ��������
protected:

	// ������Ź�������
	void RandomAttackAnims(TArray<UAnimMontage *> RandomAnims, int32 &LastAttackAnimsIndex);
	int32 LastMeleeIndex; 
	int32 LastSwordIndex; 	

	//������Ŷ���
	void RandomPlayAnims(TArray<UAnimMontage *> RandomAnims);

	// ���򲥷Ź�������
	void SequenceAttackAnims(TArray<UAnimMontage *> RandomAnims);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 SequenceAttackAnimIndex;  	// ˳�򶯻����� ������ͼ����

	// ���з����еĶ���
	void DirectionAnims(TArray<UAnimMontage *> DirectionAnims);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector CharacterDirection; 	// ��ɫ����

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MoveRightVal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MoveForwardVal;

	FVector ForwardVec;
	FVector RightVec;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RootMotion")
	float DeltaRotator = 5.f;

	// ����������ʾ
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ExhaustedStaminaPrompt();

	// ������𶯷���
	UFUNCTION(BlueprintImplementableEvent)
	void CameraShakeFeedback(bool IsOpen);

	// ��ɫת���ֵ�ٶ�
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute")
	float CharacterTurnInterpSpeed;

	// ��ȡ��ǰ����ֵ
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetCurrentStamina() const { return Stamina; };

	// ��ȡ��ǰ�������ֵ
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetMaxStamine() const { return MaxStamina; };

	// �Ƴ���������
	void RemovePlayerInput();

public:

	virtual void AttackMode() PURE_VIRTUAL(APlayer_Base::AttackMode, );

	//virtual void Roll() PURE_VIRTUAL(APlayer_Base::Roll, );

	virtual void Slide() PURE_VIRTUAL(APlayer_Base::Slide, );

	// ��������
	virtual void ChangeWeapons() PURE_VIRTUAL(APlayer_Base::ChangeWeapons, );

	// �ֽ�����
	virtual void SwordDefense()  PURE_VIRTUAL(APlayer_Base::SwordDefense, );
	virtual void StopDefense()  PURE_VIRTUAL(APlayer_Base::StopDefense, );

	// ԭ�غ���
	virtual void StepBackInPlace() PURE_VIRTUAL(APlayer_Base::StepBackInPlace, );

	// melee�������
	UFUNCTION(BlueprintCallable)
	void EnableMeleeCollision();

	// melee���뾶
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Attribute)
	float MeleeSphereCollisionRadius;

	// �ܻ�
	virtual void Affected() PURE_VIRTUAL(APlayer_Base::Affected,);

	//����
	void Die();

	// AI
public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AITarget")
	ASamurai *AITarget;

	// ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AITarget")
	TSubclassOf<ASamurai> InsAITarget;
	
	void FindAITargetPtr();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> DirectionArrow;

	// �˺�����
protected:

	// �����˺�ֵ
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DamageMechanism", meta = (ClampMin = "0.01", ClampMax = "1.0"))
	float BaseDamage; 

	// �˺���Ӱ��̶�ϵ��
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DamageMechanism", meta = (ClampMin = "0.01", ClampMax = "1.0"))
	float StaminaModifier; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DamageMechanism")
	float HitPointModifier; 

	float DamageCalculation(float BDamage, float SModifier, float HPModifier);



};
