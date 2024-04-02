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

	//拔剑动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimMontage")
	TArray<UAnimMontage *> EquipAnim;

	//攻击动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimMontage")
	TArray<UAnimMontage *> AttackAnims;

	//冲刺攻击
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimMontage")
	TArray<UAnimMontage *> RushAttackAnim;

	//受击动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimMontage")
	TArray<UAnimMontage *> InjuryAnims;

	//翻滚动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimMontage")
	TArray<UAnimMontage *> RollingAnims;

	// 属性
public:

	//是否已经装备
	UPROPERTY(BlueprintReadWrite, Category = "Attribute")
	bool bEquip;

	//是否跑步
	UPROPERTY(BlueprintReadWrite, Category = "Attribute")
	bool bRunning;

	//是否攻击
	UPROPERTY(BlueprintReadWrite, Category = "Attribute")
	bool bAttack;

	//是否翻滚
	UPROPERTY(BlueprintReadWrite, Category = "Attribute")
	bool bRolling;

	//是否受击
	UPROPERTY(BlueprintReadWrite, Category = "Attribute")
	bool bInjury;

	//是否无敌
	UPROPERTY(BlueprintReadWrite, Category = "Attribute")
	bool bIgnoreHit;

	//是否死亡
	UPROPERTY(BlueprintReadWrite, Category = "Attribute")
	bool bDie;

	//血量
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
	float HitPoint;

	//最大血量
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
	float MaxHitPoint;


public:

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetAICharacterHP();

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetAICharacterMaxHP();

	// 目标
public:

	UPROPERTY(BlueprintReadOnly, Category = "Target")
	ACharacter_Base *TargetPawn;

	// Pawn参照
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target")
	TSubclassOf<ACharacter_Base> InsPawn;


	void FindTargetPawn();

	void RunningMovement(bool IsRun);



public:

	UFUNCTION(BlueprintCallable)
	void DrawTheSword();

	ASamuraiAiController *AIController;

};
