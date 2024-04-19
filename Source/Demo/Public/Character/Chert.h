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

	// Í··¢×é¼þ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GroomComponent", meta = (AllowPrivateAccess = "Ture"))
	TObjectPtr<UGroomComponent> Hair;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GroomComponent", meta = (AllowPrivateAccess = "Ture"))
	TObjectPtr<UGroomComponent> Brows;

	// ½£ÇÊ
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Scabbard;

	// ½£
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Sword;

	// ½£ºÛ
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraComponent> SwordScar;

	// ¶¯»­
private:

	// ½üÕ½¹¥»÷
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimMontage", meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage *> MeleeCombatAnims;

	// »¬ÐÐ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AnimMontage, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage *> SlideAnims;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AnimMontage, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage *> AffectedAnims;

	// ³Ö½£·ÀÓù
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AnimMontage, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage *> SwordDefenseAnims;

	// ÆÆ·À
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AnimMontage, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage *> DestroyDefenseAnims;

	// ÊôÐÔ
protected:


public:

	AChert();
	// ¹¥»÷·½Ê½
	virtual void AttackMode() override;

	void MeleeCombatAttack();
	bool IsCanMeleeCombatAttack();

	void SwordAttack();
	bool IsCanSwordAttack();

	// ÇÐ»»ÎäÆ÷
	virtual void ChangeWeapons() override;
	bool IsCanChangeWeapon();

	// ³Ö½£·ÀÓù
	virtual void SwordDefense() override;
	bool IsCanSwordDefense();

	virtual void StopDefense() override;

	// »¬ÐÐ
	virtual void Slide() override;
	bool IsCanSlide();

	// ÊÜ»÷
	virtual void Affected() override;

	//void MeleeAffected();
	//void SwordAffected();
	bool IsCanAffected();

	void DestroyDefense();

	UFUNCTION(BlueprintCallable)
	void GetClosestAI(float Radius, AActor *&TargetActor, bool &IsCollisionAnyItem);

	TArray<AActor *> LockActors;

	AActor *TargetActor;

	float DistanceofPlayerAndAI;

	bool IsCollisionAnyItem;

	bool IsLock;

	void LockAI();


	// Á¬ÕÐ
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UComboGuide *ComboGuide;

};
