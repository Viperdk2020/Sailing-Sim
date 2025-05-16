
using UnrealBuildTool;
using System.IO;
public class SailSimPhysics : ModuleRules
{
    public SailSimPhysics(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new[]
        {
            "Core", "CoreUObject", "Engine",
            "RenderCore", "RHI", "RHICore", "RenderGraph"
        });

        // Map plugin-level Shaders folder
       // string PluginDir = Path.GetFullPath(Path.Combine(ModuleDirectory,  "..", "..""));
      //  AdditionalShaderDirectories.Add(Path.Combine(PluginDir, "Shaders"));
    }
}
