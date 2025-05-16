
using UnrealBuildTool;
public class SailSimRendering : ModuleRules
{
    public SailSimRendering(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new[]
        {
            "Core", "CoreUObject", "Engine",
            "RenderCore", "RHI", "RHICore", "RenderGraph", "ShaderCore",
            "SailSimPhysics"
        });
    }
}
