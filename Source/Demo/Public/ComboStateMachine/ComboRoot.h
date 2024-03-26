// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "ComboStateMachine/Core/ActionStage.h"

#include "ComboRoot.generated.h"

class UComboStorage;
class UComboContext;
enum class EActionLifeCycle : uint8;
enum class EAction : uint8;

/**
 * 
 */
UCLASS(BlueprintType)
class DEMO_API UComboRoot : public UObject, public IActionStage
{
	GENERATED_BODY()


	UComboRoot();

public:
	/*
	UPROPERTY(BlueprintReadOnly)
	EAction Action;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UComboContext> Context;

	UPROPERTY(BlueprintReadOnly)
	bool bIsCachedInput = false; // �Ƿ񻺳�

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UComboStorage> Storage; // ���д洢��
	*/
	/*
	virtual void Start();

	virtual void Pre(AChert *Character = nullptr) override;

	UFUNCTION(BlueprintCallable)
	virtual void Exec(AChert *BaseCharacter = nullptr) override;

	UFUNCTION(BlueprintCallable)
	virtual void Derive_Start(AChert *BaseCharacter = nullptr) override;

	UFUNCTION(BlueprintCallable)
	virtual void Gap(AChert *BaseCharacter = nullptr) override;

	UFUNCTION(BlueprintCallable)
	virtual void Derive_End(AChert *BaseCharacter = nullptr) override;

	UFUNCTION(BlueprintCallable)
	virtual void End(AChert *BaseCharacter = nullptr) override;

protected:

	virtual bool IsCanCombo();

	virtual void Reset();

	virtual void Toggle();

	*/
};
