// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Endless_Runner : ModuleRules
{
	public Endless_Runner(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG" });
	}
}
