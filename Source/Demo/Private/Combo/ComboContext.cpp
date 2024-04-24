// Fill out your copyright notice in the Description page of Project Settings.


#include "Combo/ComboContext.h"

UComboContext::UComboContext()
{
	CurrentComboAction = CreateDefaultSubobject<UComboNode>(TEXT("CurrentCombo"));

	CurrentComboAction->MaxActionIndex = 4;

	// combo1 子招式1
	UComboNode *DeriveCombo1 = CreateDefaultSubobject<UComboNode>(TEXT("DeriveCombo1"));
	DeriveCombo1->MaxActionIndex = 2;
	DeriveCombo1->Action = EComboActions::Combo_1_1;
	CurrentComboAction->AddChildCombo(1, DeriveCombo1);

	// combo1 子招式2
	UComboNode *DeriveCombo2 = CreateDefaultSubobject<UComboNode>(TEXT("DeriveCombo2"));
	DeriveCombo2->MaxActionIndex = 2;
	DeriveCombo2->Action = EComboActions::Combo_1_2;
	CurrentComboAction->AddChildCombo(2, DeriveCombo2);

	// combo1 子招式3
	UComboNode *DeriveCombo3 = CreateDefaultSubobject<UComboNode>(TEXT("DeriveCombo3"));
	DeriveCombo3->MaxActionIndex = 2;
	DeriveCombo3->Action = EComboActions::Combo_1_3;
	CurrentComboAction->AddChildCombo(3, DeriveCombo3);

	/*
	UComboNode *DeriveCombo4 = CreateDefaultSubobject<UComboNode>(TEXT("DeriveCombo4"));
	DeriveCombo4->MaxActionIndex = 1;
	DeriveCombo4->Action = EComboActions::Combo_1_4;
	CurrentComboAction->AddChildCombo(4, DeriveCombo4);
	*/

	ComboMapping.Add(CurrentComboAction->Action, CurrentComboAction);
	ComboMapping.Add(DeriveCombo1->Action, DeriveCombo1);
	ComboMapping.Add(DeriveCombo2->Action, DeriveCombo2);
	ComboMapping.Add(DeriveCombo3->Action, DeriveCombo3);
	//ComboMapping.Add(DeriveCombo4->Action, DeriveCombo4);

	/*
	CurrentComboAction = CreateDefaultSubobject<UComboNode>(TEXT("CurrentCombo"));
	ComboMapping.Add(CurrentComboAction->Action, CurrentComboAction);

	UComboNode *DeriveCombo1 = CreateDefaultSubobject<UComboNode>(TEXT("DeriveCombo1"));
	//...
	//...
	CurrentComboAction->AddChildCombo(3, DeriveCombo3);
	//...
	ComboMapping.Add(DeriveCombo1->Action, DeriveCombo1);
	// ... 其余子节点同上
	*/

}

UComboNode *UComboContext::FindRootCombo(const EComboActions RootAction)
{
	UComboNode **Combo = ComboMapping.Find(RootAction);
	if (Combo)
	{
		return *Combo;
	}
	return nullptr;
}