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

	// ͷ�����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GroomComponent", meta = (AllowPrivateAccess = "Ture"))
	TObjectPtr<UGroomComponent> Hair;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GroomComponent", meta = (AllowPrivateAccess = "Ture"))
	TObjectPtr<UGroomComponent> Brows;

	// ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Scabbard;

	// ��
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Sword;

	// ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraComponent> SwordScar;

	// ����
private:

	// ��ս����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimMontage", meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage *> MeleeCombatAnims;

	// ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AnimMontage, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage *> SlideAnims;


	// ����
protected:




	// ����ת��
public:

	AChert();
	// ������ʽ
	virtual void AttackMode() override;

	void MeleeCombatAttack();
	bool IsCanMeleeCombatAttack();

	void SwordAttack();
	bool IsCanSwordAttack();

	// �л�����
	virtual void ChangeWeapons() override;
	bool IsCanChangeWeapon();

	// �ֽ�����
	virtual void SwordDefense() override;
	bool IsCanSwordDefense();

	virtual void StopDefense() override;

	// ����
	virtual void Slide() override;
	bool IsCanSlide();

	// �ܻ�
	virtual void Affected() override;

	void MeleeAffected();
	void SwordAffected();
	bool IsCanAffected();


	// ����
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UComboGuide *ComboGuide;

};
