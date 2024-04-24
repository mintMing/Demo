#pragma once

#include "EventManager.generated.h"

DECLARE_DELEGATE_OneParam(FOpenSettlementUI, bool);

UCLASS(BlueprintType)
class UEventManager : public UObject
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "EventManager")
	static UEventManager *GetInstancePtr();

private:
	static UEventManager *S_Instance;

public:
	
	FOpenSettlementUI OpenUI;
};