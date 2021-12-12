#include "GameplayDebuggerCategory_Generic.h"

#include "GameFramework/PlayerController.h"

//CTOR/DTOR & VIRTUAL FUNCTIONS

FGameplayDebuggerCategory_Generic::FGameplayDebuggerCategory_Generic() : Data{}
{
	bShowOnlyWithDebugActor = false;
}

void FGameplayDebuggerCategory_Generic::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
	if (OwnerPC && DebugActor)
		Data.ActorName = OwnerPC->GetName();
}

void FGameplayDebuggerCategory_Generic::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
	if (OwnerPC && !Data.ActorName.IsEmpty())
		CanvasContext.Printf(TEXT("{yellow}Name = {lime}%s"), *Data.ActorName);
}

// FUNCTIONS

TSharedRef<FGameplayDebuggerCategory> FGameplayDebuggerCategory_Generic::MakeInstance()
{
	return MakeShared<FGameplayDebuggerCategory_Generic>();
}
