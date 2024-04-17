// Fill out your copyright notice in the Description page of Project Settings.


#include "Combo/ComboNode.h"

UComboNode::UComboNode()
{
	MaxActionIndex = 3;
	CurrentActionIndex = 0;
	Action = EComboActions::Combo_1;
	RootAction = Action;
	ActionStage = EActionStages::End;
}

bool UComboNode::AddChildCombo(const int ActionIndex, UComboNode *Combo)
{
	if (ActionIndex <= 0 || ActionIndex > MaxActionIndex)
	{
		return false;
	}

	if (Action != RootAction)
	{
		return false;
	}

	if (Combo->Action == Action)
	{
		return false;
	}

	Combo->RootAction = Action;

	ChildComboMapping.Add(ActionIndex, Combo);

	return true;
}

