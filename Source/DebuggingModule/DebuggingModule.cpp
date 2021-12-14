#include "DebuggingModule.h"

#include "GameplayDebugger.h"
#include "GameplayDebuggerCategory_Generic.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

#define LOCTEXT_NAMESPACE "FDebuggingModule"

void FDebuggingModule::StartupModule()
{
	IGameplayDebugger& GameplayDebugger = IGameplayDebugger::Get();
	GameplayDebugger.RegisterCategory("Generic", IGameplayDebugger::FOnGetCategory::CreateStatic(&FGameplayDebuggerCategory_Generic::MakeInstance),
	                                  EGameplayDebuggerCategoryState::EnabledInGameAndSimulate, 5);
	GameplayDebugger.NotifyCategoriesChanged();
}

void FDebuggingModule::ShutdownModule()
{
	if (IGameplayDebugger::IsAvailable())
	{
		IGameplayDebugger& GameplayDebugger = IGameplayDebugger::Get();
		GameplayDebugger.UnregisterCategory("Generic");
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDebuggingModule, DebuggingModule);
