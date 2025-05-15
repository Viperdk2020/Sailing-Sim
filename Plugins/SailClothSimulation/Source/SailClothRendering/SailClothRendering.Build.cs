using System.IO;
using UnrealBuildTool;

public class SailClothRendering : ModuleRules
{
    public SailClothRendering(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "RenderCore",
            "RHI",
            "SailClothPhysics"
        });

        PrivateDependencyModuleNames.AddRange(new string[] { "SailClothPhysics" });

        // Corrected paths using ModuleDirectory
        PublicIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "Public")   });
        PrivateIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "Private")});
    }
}
