// Fill out your copyright notice in the Description page of Project Settings.


#include "Combo/ComboGuide.h"

UComboGuide::UComboGuide()
{
	ComboContext = CreateDefaultSubobject<UComboContext>(TEXT("ComboContext"));
}

void UComboGuide::Pre()
{
	if (!IsCanCombo())
	{
		return;
	}

	if (ComboContext->CurrentComboAction->CurrentActionIndex >= ComboContext->CurrentComboAction->MaxActionIndex)
	{
		if (IsActionIsChild())
		{
			if (ComboContext->CurrentComboAction->ActionStage == EActionStages::Attack)
			{
				ResetRootAction = true;
				return;
			}
			if (ComboContext->CurrentComboAction->ActionStage == EActionStages::Derive)
			{
				RootToggleToChild();
			}
		}
		ComboContext->CurrentComboAction->CurrentActionIndex = 0;
	}

	if (ComboContext->CurrentComboAction->ActionStage == EActionStages::Attack)
	{
		SaveAttack = true;
		return;
	}

	if (ComboContext->CurrentComboAction->ActionStage == EActionStages::Gap)
	{
		if (UComboNode **ChildAction = ComboContext->CurrentComboAction->ChildComboMapping.Find(ComboContext->CurrentComboAction->CurrentActionIndex))
		{
			UComboNode *Node = *ChildAction;

			Node->CurrentActionIndex = 0;

			ComboContext->CurrentComboAction = Node;
		}
	}

	ComboContext->CurrentComboAction->ActionStage = EActionStages::Pre;
	ComboContext->CurrentComboAction->CurrentActionIndex++;
}

void UComboGuide::Attack()
{
	ComboContext->CurrentComboAction->ActionStage = EActionStages::Attack;
}

void UComboGuide::Derive()
{
	ComboContext->CurrentComboAction->ActionStage = EActionStages::Derive;

	if (ResetRootAction)
	{
		RootToggleToChild();
		ComboContext->CurrentComboAction->CurrentActionIndex = 0;
		ResetRootAction = false;
	}
	if (SaveAttack)
	{
		Pre();
		SaveAttack = false;
	}
}

void UComboGuide::Gap()
{
	ComboContext->CurrentComboAction->ActionStage = EActionStages::Gap;
}

void UComboGuide::End()
{
	if (ComboContext->CurrentComboAction->ActionStage == EActionStages::Gap ||
		ComboContext->CurrentComboAction->ActionStage == EActionStages::Derive)
	{
		ComboContext->CurrentComboAction->ActionStage = EActionStages::End;

		ResetCombo();
	}
}

bool UComboGuide::IsCanCombo()
{
	return ComboContext->CurrentComboAction->ActionStage == EActionStages::Attack ||
		ComboContext->CurrentComboAction->ActionStage == EActionStages::Derive ||
		ComboContext->CurrentComboAction->ActionStage == EActionStages::Gap ||
		ComboContext->CurrentComboAction->ActionStage == EActionStages::End;
}

void UComboGuide::ResetCombo()
{
	RootToggleToChild();
	ComboContext->CurrentComboAction->CurrentActionIndex = 0;
	ComboContext->CurrentComboAction->ActionStage = EActionStages::End;
	SaveAttack = false;
}

bool UComboGuide::IsActionIsChild() const
{
	return ComboContext->CurrentComboAction->Action != ComboContext->CurrentComboAction->RootAction;
}

void UComboGuide::RootToggleToChild() const
{
	if (IsActionIsChild())
	{
		if (UComboNode *FindRootCombo = ComboContext->FindRootCombo(ComboContext->CurrentComboAction->RootAction))
		{
			ComboContext->CurrentComboAction = FindRootCombo;
		}
	}
}


