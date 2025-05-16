using System.IO;
using UnrealBuildTool;

public class SailCloth : ModuleRules
{
    public SailCloth(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "RenderCore",
            "RHI",
            "SailClothPhysics",
            "SailClothRendering"
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
        PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));

    }
}
