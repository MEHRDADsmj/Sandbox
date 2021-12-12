#pragma once

#include "CoreMinimal.h"
#include "GameplayDebuggerCategory.h"

class FGameplayDebuggerCategory_Generic : public FGameplayDebuggerCategory
{
	//CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	FGameplayDebuggerCategory_Generic();

	virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;
	virtual void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;

	// FUNCTIONS
public:
	static TSharedRef<FGameplayDebuggerCategory> MakeInstance();

	// PROPERTIES
protected:
	struct FData
	{
		FString ActorName;
	};

	FData Data;
};
