// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

// ReSharper disable InconsistentNaming

public class MITHT_ProjectEditorTarget : TargetRules
{
	public MITHT_ProjectEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("MITHT_Project");
	}
}
