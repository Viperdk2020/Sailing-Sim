// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
// Workaround for Clang Win64 missing kernel32 symbols
using System;
using System.IO;

public class Sailing : ModuleRules
{
	public Sailing(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

       // Target.CppStandard = CppStandardVersion.Cpp20;

        PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject", 
			"Engine",
			"InputCore", 
			"GeometryFramework", 
			"GeometryCore",
			"DynamicMesh", 
			"GeometryScriptingCore",
            "Chaos",
            "ChaosCloth",
            "ChaosClothAssetEngine"
        });


        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicSystemLibraries.Add("kernel32.lib");
            PublicSystemLibraries.Add("user32.lib");
        }



        PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add();

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
