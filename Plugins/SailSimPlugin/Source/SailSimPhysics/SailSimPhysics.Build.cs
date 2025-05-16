// SailSimPhysics.Build.cs

using UnrealBuildTool;

public class SailSimPhysics : ModuleRules
{
    public SailSimPhysics(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "RenderCore",
            "RHI",
            "Projects"
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            // Add private dependencies here if needed
        });

        PublicIncludePaths.AddRange(new string[]
        {
            // Add any public include paths here, e.g.:
             "SailSimPhysics/Public"
        });

        PrivateIncludePaths.AddRange(new string[]
        {
            // Add any private include paths here, e.g.:
             "SailSimPhysics/Private"
        });

        // If you use shaders in Shaders/ or plugin, add:
         RuntimeDependencies.Add("$(PluginDir)/Shaders/XPBDStretchCS.usf");
         RuntimeDependencies.Add("$(PluginDir)/Shaders/XPBDBendCS.usf");
         RuntimeDependencies.Add("$(PluginDir)/Shaders/VLMJacobiCS.usf");
    }
}
