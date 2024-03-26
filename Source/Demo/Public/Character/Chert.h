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

	// 剑攻击
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimMontage", meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage *> SwordAttackAnims;

	// 近战翻滚
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AnimMontage, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage *> MeleeCombatRollAnims;

	// 持剑翻滚
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AnimMontage, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage *> SwordRollAnims;

	// 滑行
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AnimMontage, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage *> SlideAnims;

	// 剑 蓄力攻击
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AnimMontage, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage *> SwordChargeAttackAnim;

	// 属性
protected:

	// 蓄力攻击减少的体力值
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute")
	float ChargeAttackSubStamina;


	// 动作转换
public:
	AChert();
	// 攻击方式
	virtual void AttackMode() override;

	void MeleeCombatAttack();
	bool IsCanMeleeCombatAttack();

	void SwordAttack();
	bool IsCanSwordAttack();

	// 翻滚
	UFUNCTION(BlueprintCallable)
	virtual void Roll() override;

	void MeleeCombatRoll();
	bool IsCanMeleeCombatRoll();

	void SwordRoll();
	bool IsCanSwordRoll();

	// 切换武器
	virtual void ChangeWeapons() override;
	bool IsCanChangeWeapon();

	// 持剑防御
	virtual void SwordDefense() override;
	bool IsCanSwordDefense();

	virtual void StopDefense() override;

	// 蓄力攻击
	void ChargeAttack();
	bool IsCanChargeAttack();


	// 滑行
	virtual void Slide() override;
	bool IsCanSlide();

};
