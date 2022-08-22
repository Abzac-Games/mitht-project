// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

// ReSharper disable InconsistentNaming

public class MITHT_Project : ModuleRules
{
	public MITHT_Project(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		var modules = new[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"HeadMountedDisplay",
			"ActorInteractionPlugin",
			"SMSystem"
		};
		PublicDependencyModuleNames.AddRange(modules);
	}
}
