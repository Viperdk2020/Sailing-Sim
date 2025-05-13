// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class SailingTarget : TargetRules
{
	public SailingTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
        //TargetBuildEnvironment =;
        bOverrideBuildEnvironment = true;
       // BuildEnvironment = TargetBuildEnvironment.Unique;
        DefaultBuildSettings = BuildSettingsVersion.Latest;
	//	IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_1;

        ExtraModuleNames.AddRange( new string[] { "Sailing" } );
	}
}
