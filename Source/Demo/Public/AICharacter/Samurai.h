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
	// 拔剑动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimMontage")
	TArray<UAnimMontage *> EquipAnim;

	// 攻击动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimMontage")
	TArray<UAnimMontage *> AttackAnims;

	// 冲刺攻击
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimMontage")
	TArray<UAnimMontage *> RushAttackAnim;

	// 受击动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimMontage")
	TArray<UAnimMontage *> AffectedAnims;

	// 翻滚动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimMontage")
	TArray<UAnimMontage *> RollingAnims;


	// 属性
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

	// 功能
public:

	UFUNCTION(BlueprintPure, BlueprintCallable)
	FORCEINLINE float GetAICharacterHP() { return HitPoint; };

	UFUNCTION(BlueprintPure, BlueprintCallable)
	FORCEINLINE float GetAICharacterMaxHP() { return MaxHitPoint; };

	void RandomPlayMontage(TArray<UAnimMontage *> Animaitons);
	int32 LastAttackAnimsIndex;

	// 受击音效
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayAffectedSound();

	// 碰撞开关
	UFUNCTION(BlueprintCallable)
	void EnableAttackCollision();

	float SwordSphereCollisionRadius;

	FVector GetTargetPosition();

public:

	// 受击逻辑
	void AccumulatedHit();   // 累计被攻击次数
	FTimerHandle AttackTimerHandle;
	int32 AttackedCount;
	void ResetAttackCount();	// 重置被攻击次数
	void ApplyBleedingDamage(); // 应用出血效果伤害

	UFUNCTION(BlueprintCallable)
	void Affected();
	bool IsCanAffected();

	// 攻击
	void Attack();
	bool IsCanAttack();

	void Roll();

	void Death();
	// 死亡UI事件
	void DeathUI();

	void RushThump();
	bool IsCanRushThump();
	void EnableThump();
	
	// 重攻击方向
	void ThumpMovement(int32 Direction);
	int32 ThumpDirection; 	

	UFUNCTION(BlueprintCallable)
	void RushThumpDistance(float Lerp);

	FTimerHandle DelayRandomThumb;
	FTimerHandle DelayFindPlayerPtr;

	// 目标
public:

	UPROPERTY(BlueprintReadOnly, Category = "Target")
	ACharacter_Base *TargetPawn;

	// Pawn参照
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target")
	TSubclassOf<ACharacter_Base> InsPawn;

	// 重攻击的目标位置
	FVector RushAttackPosition;

	void FindTargetPawn();

	void RunMovement(bool IsRun);


public:

	UFUNCTION(BlueprintCallable)
	void DrawTheSword();

	ASamuraiController *AIController;
	
};
