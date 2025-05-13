using UnrealBuildTool;
using System.IO;

public class SailClothShaders : ModuleRules
{
    public SailClothShaders(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
        PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",           // basic types
            "CoreUObject",    // FVector etc.
            "RenderCore",     // FGlobalShader, RenderGraphUtils, ComputeShaderUtils
            "RHI",             // FRHI* and buffer APIs
            "Projects"         // if you use IPluginManager in your module (shader directory mapping)
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
