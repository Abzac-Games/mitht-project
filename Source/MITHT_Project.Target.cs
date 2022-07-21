// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

// ReSharper disable InconsistentNaming

public class MITHT_ProjectTarget : TargetRules
{
	public MITHT_ProjectTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("MITHT_Project");
	}
}
