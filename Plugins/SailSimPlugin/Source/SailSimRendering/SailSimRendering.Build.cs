using UnrealBuildTool;
// Workaround for Clang Win64 missing kernel32 symbols
using System;
using System.IO;

public class SailSimRendering : ModuleRules
{
    public SailSimRendering(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;


        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicSystemLibraries.Add("kernel32.lib");
            PublicSystemLibraries.Add("user32.lib");
        }


        PublicIncludePaths.AddRange(
            new string[] {
                "D:\\UE5\\Unreal Projects\\Sailing\\Plugins\\SailSimPlugin\\Source\\SailSimRendering\\Public"
            }
        );

        PrivateIncludePaths.AddRange(
            new string[] {
                "D:\\UE5\\Unreal Projects\\Sailing\\Plugins\\SailSimPlugin\\Source\\SailSimRendering\\Private",
                "D:\\UE5\\Unreal Projects\\Sailing\\Plugins\\SailSimPlugin\\Source\\SailSimRendering\\Public"
            }
        );

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "RenderCore",
                "RHI"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "SailSimCore",
                "SailSimPhysics",
                "Projects",
                "Slate",
                "SlateCore"
            }
        );

        if (Target.bBuildEditor)
        {
            PrivateDependencyModuleNames.Add("UnrealEd");
        }
    }
}
