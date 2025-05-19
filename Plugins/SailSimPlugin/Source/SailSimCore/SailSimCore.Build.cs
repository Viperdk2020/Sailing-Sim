
using UnrealBuildTool;
// Workaround for Clang Win64 missing kernel32 symbols
using System;
using System.IO;
public class SailSimCore : ModuleRules
{
    public SailSimCore(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new[] { 
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "UMG",
            "Slate",
            "SlateCore"
        });
      
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicSystemLibraries.Add("kernel32.lib");
            PublicSystemLibraries.Add("user32.lib");
        }

    }
}
