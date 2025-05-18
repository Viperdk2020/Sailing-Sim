using UnrealBuildTool;
// Workaround for Clang Win64 missing kernel32 symbols
using System;
using System.IO;

public class SailSimPhysics : ModuleRules
{
    public SailSimPhysics(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "RenderCore",
            "RHI",
            "Projects"
        });



        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicSystemLibraries.Add("kernel32.lib");
            PublicSystemLibraries.Add("user32.lib");
            RuntimeDependencies.Add("$(EngineDir)/Binaries/ThirdParty/Windows/DirectX/x64/d3dcompiler_47.dll");

        }





        PrivateDependencyModuleNames.AddRange(new string[] {
            // Add private dependencies if needed
        });

        // Use ModuleDirectory for relative include paths inside your module
        PublicIncludePaths.AddRange(new string[] {
            Path.Combine(ModuleDirectory, "Public")
        });

        PrivateIncludePaths.AddRange(new string[] {
            Path.Combine(ModuleDirectory, "Private")
        });
    }
}
