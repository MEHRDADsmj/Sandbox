#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class FDebuggingModule : public IModuleInterface
{
	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	FDebuggingModule() = default;

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
