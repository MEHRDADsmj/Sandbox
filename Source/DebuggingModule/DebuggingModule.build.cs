// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DebuggingModule : ModuleRules
{
	public DebuggingModule(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[] {"Core", "CoreUObject", "GameplayDebugger"});
	}
}