using UnrealBuildTool;
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
