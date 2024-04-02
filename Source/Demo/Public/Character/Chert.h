// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Character_Base.h"

#include "Chert.generated.h"

/**
 * 
 */

class UGroomComponent;
class UAnimMontage;
class UNiagaraComponent;
class USkeletalMeshComponent;
class UStaticMeshComponent;
class UMotionWarpingComponent;

class UComboGuide;

UCLASS()
class DEMO_API AChert : public ACharacter_Base
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

private:

	// 头发组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GroomComponent", meta = (AllowPrivateAccess = "Ture"))
	TObjectPtr<UGroomComponent> Hair;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GroomComponent", meta = (AllowPrivateAccess = "Ture"))
	TObjectPtr<UGroomComponent> Brows;

	// 剑鞘
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Scabbard;

	// 剑
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Sword;

	// 剑痕
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraComponent> SwordScar;

	// 动画
private:

	// 近战攻击
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimMontage", meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage *> MeleeCombatAnims;

	// 滑行
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AnimMontage, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage *> SlideAnims;


	// 属性
protected:




	// 动作转换
public:

	AChert();
	// 攻击方式
	virtual void AttackMode() override;

	void MeleeCombatAttack();
	bool IsCanMeleeCombatAttack();

	void SwordAttack();
	bool IsCanSwordAttack();

	// 切换武器
	virtual void ChangeWeapons() override;
	bool IsCanChangeWeapon();

	// 持剑防御
	virtual void SwordDefense() override;
	bool IsCanSwordDefense();

	virtual void StopDefense() override;

	// 滑行
	virtual void Slide() override;
	bool IsCanSlide();

	// 受击
	virtual void Affected() override;

	void MeleeAffected();
	void SwordAffected();
	bool IsCanAffected();


	// 连招
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UComboGuide *ComboGuide;

};
