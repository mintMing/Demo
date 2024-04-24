#include "Entrusted/EventManager.h"

UEventManager *UEventManager::S_Instance = nullptr;

UEventManager *UEventManager::GetInstancePtr()
{
	if (S_Instance == nullptr)
	{
		S_Instance = NewObject<UEventManager>();
		S_Instance->AddToRoot();
	}
	return S_Instance;
}