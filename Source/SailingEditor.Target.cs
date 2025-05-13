// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class SailingEditorTarget : TargetRules
{
	public SailingEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
        bOverrideBuildEnvironment = true;
        DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "Sailing" } );
	}
}
