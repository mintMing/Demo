// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AICharacter/AICharacter_Base.h"
#include "AISamurai.generated.h"

/**
 * 
 */

class USkeletalMeshComponent;
class UBoxComponent;
class ACharacter_Base;


class ASamuraiAiController;

UCLASS()
class DEMO_API AAISamurai : public AAICharacter_Base
{
	GENERATED_BODY()

	AAISamurai();

	virtual void BeginPlay() override;
	
private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "Ture"))
	TObjectPtr<USkeletalMeshComponent> Sword;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "Ture"))
	TObjectPtr<UBoxComponent> HitColl;


public:

	//�ν�����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimMontage")
	TArray<UAnimMontage *> EquipAnim;

	//��������
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimMontage")
	TArray<UAnimMontage *> AttackAnims;

	//��̹���
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimMontage")
	TArray<UAnimMontage *> RushAttackAnim;

	//�ܻ�����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimMontage")
	TArray<UAnimMontage *> InjuryAnims;

	//��������
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimMontage")
	TArray<UAnimMontage *> RollingAnims;

	// ����
public:

	//�Ƿ��Ѿ�װ��
	UPROPERTY(BlueprintReadWrite, Category = "Attribute")
	bool bEquip;

	//�Ƿ��ܲ�
	UPROPERTY(BlueprintReadWrite, Category = "Attribute")
	bool bRunning;

	//�Ƿ񹥻�
	UPROPERTY(BlueprintReadWrite, Category = "Attribute")
	bool bAttack;

	//�Ƿ񷭹�
	UPROPERTY(BlueprintReadWrite, Category = "Attribute")
	bool bRolling;

	//�Ƿ��ܻ�
	UPROPERTY(BlueprintReadWrite, Category = "Attribute")
	bool bInjury;

	//�Ƿ��޵�
	UPROPERTY(BlueprintReadWrite, Category = "Attribute")
	bool bIgnoreHit;

	//�Ƿ�����
	UPROPERTY(BlueprintReadWrite, Category = "Attribute")
	bool bDie;

	//Ѫ��
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
	float HitPoint;

	//���Ѫ��
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
	float MaxHitPoint;


public:

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetAICharacterHP();

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetAICharacterMaxHP();

	// Ŀ��
public:

	UPROPERTY(BlueprintReadOnly, Category = "Target")
	ACharacter_Base *TargetPawn;

	// Pawn����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target")
	TSubclassOf<ACharacter_Base> InsPawn;


	void FindTargetPawn();

	void RunningMovement(bool IsRun);



public:

	UFUNCTION(BlueprintCallable)
	void DrawTheSword();

	ASamuraiAiController *AIController;

};
