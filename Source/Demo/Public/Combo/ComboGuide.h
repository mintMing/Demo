// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Combo/ActionStage.h"
#include "Combo/ComboContext.h"

#include "ComboGuide.generated.h"

/**
 * 
 */


class ACharacter_Base;

UCLASS(BlueprintType)
class DEMO_API UComboGuide : public UObject, public IActionStage
{
	GENERATED_BODY()
	
	UComboGuide();

public:

	UPROPERTY(BlueprintReadOnly)
	UComboContext *ComboContext;

	UPROPERTY(BlueprintReadOnly)
	ACharacter_Base *Performer;
	
	UPROPERTY(BlueprintReadOnly)
	bool SaveAttack = false;

	UPROPERTY(BlueprintReadOnly)
	bool ResetRootAction = false;

public:

	virtual void Pre() override;

	UFUNCTION(BlueprintCallable)
	virtual void Attack() override;

	UFUNCTION(BlueprintCallable)
	virtual void Derive() override;

	UFUNCTION(BlueprintCallable)
	virtual void Gap() override;

	UFUNCTION(BlueprintCallable)
	virtual void End() override;


protected:
	virtual bool IsCanCombo();

	virtual void ResetCombo();

private:

	bool IsActionIsChild() const;

	void RootToggleToChild() const;

};
