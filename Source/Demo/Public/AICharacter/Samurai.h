// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "AICharacter/LockSystem.h"

#include "Samurai.generated.h"


class USkeletalMeshComponent;
class UBoxComponent;
class ACharacter_Base;
class ASamuraiController;
enum class EDamageLevel : uint8;

UCLASS()
class DEMO_API ASamurai : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASamurai();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "Ture"))
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "Ture"))
	TObjectPtr<UBoxComponent> HitColl;

protected:
	// �ν�����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimMontage")
	TArray<UAnimMontage *> EquipAnim;

	// ��������
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimMontage")
	TArray<UAnimMontage *> AttackAnims;

	// ��̹���
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimMontage")
	TArray<UAnimMontage *> RushAttackAnim;

	// �ܻ�����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimMontage")
	TArray<UAnimMontage *> AffectedAnims;

	// ��������
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimMontage")
	TArray<UAnimMontage *> RollingAnims;


	// ����
public:

	UPROPERTY(BlueprintReadWrite, Category = "Attribute")
	bool bIsEquip;

	UPROPERTY(BlueprintReadWrite, Category = "Attribute")
	bool bIsRun;

	UPROPERTY(BlueprintReadWrite, Category = "Attribute")
	bool bIsAttack;

	UPROPERTY(BlueprintReadWrite, Category = "Attribute")
	bool bIsRoll;

	UPROPERTY(BlueprintReadWrite, Category = "Attribute")
	bool bIsAffected;

	UPROPERTY(BlueprintReadWrite, Category = "Attribute")
	bool bIsIgnoreHit;

	UPROPERTY(BlueprintReadWrite, Category = "Attribute")
	bool bIsDeath;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
	float HitPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
	float MaxHitPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
	EDamageLevel DamageLevel;

	// ����
public:

	UFUNCTION(BlueprintPure, BlueprintCallable)
	FORCEINLINE float GetAICharacterHP() { return HitPoint; };

	UFUNCTION(BlueprintPure, BlueprintCallable)
	FORCEINLINE float GetAICharacterMaxHP() { return MaxHitPoint; };

	void RandomPlayMontage(TArray<UAnimMontage *> Animaitons);
	int32 LastAttackAnimsIndex;

	// �ܻ���Ч
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayAffectedSound();

	// ��ײ����
	UFUNCTION(BlueprintCallable)
	void EnableAttackCollision();

	float SwordSphereCollisionRadius;

	FVector GetTargetPosition();

public:

	// �ܻ��߼�
	void AccumulatedHit();   // �ۼƱ���������
	FTimerHandle AttackTimerHandle;
	int32 AttackedCount;
	void ResetAttackCount();	// ���ñ���������
	void ApplyBleedingDamage(); // Ӧ�ó�ѪЧ���˺�

	UFUNCTION(BlueprintCallable)
	void Affected();
	bool IsCanAffected();

	// ����
	void Attack();
	bool IsCanAttack();

	void Roll();

	void Death();
	// ����UI�¼�
	void DeathUI();

	void RushThump();
	bool IsCanRushThump();
	void EnableThump();
	
	// �ع�������
	void ThumpMovement(int32 Direction);
	int32 ThumpDirection; 	

	UFUNCTION(BlueprintCallable)
	void RushThumpDistance(float Lerp);

	FTimerHandle DelayRandomThumb;
	FTimerHandle DelayFindPlayerPtr;

	// Ŀ��
public:

	UPROPERTY(BlueprintReadOnly, Category = "Target")
	ACharacter_Base *TargetPawn;

	// Pawn����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target")
	TSubclassOf<ACharacter_Base> InsPawn;

	// �ع�����Ŀ��λ��
	FVector RushAttackPosition;

	void FindTargetPawn();

	void RunMovement(bool IsRun);


public:

	UFUNCTION(BlueprintCallable)
	void DrawTheSword();

	ASamuraiController *AIController;
	
};
