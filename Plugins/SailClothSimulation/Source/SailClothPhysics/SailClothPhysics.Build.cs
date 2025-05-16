using System.IO;
using UnrealBuildTool;

public class SailClothPhysics : ModuleRules
{
    public SailClothPhysics(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "RHI",
            "RenderCore"
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {

        });

        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
        PrivateIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "Private"), "SailClothPhysics/Private/Kernels" });
    }
}
