using UnrealBuildTool;

public class SailSimRendering : ModuleRules
{
    public SailSimRendering(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[] {
                "SailSimPlugin/Source/SailSimRendering/Public"
            }
        );

        PrivateIncludePaths.AddRange(
            new string[] {
                "SailSimPlugin/Source/SailSimRendering/Private",
                "SailSimPlugin/Source/SailSimPhysics/Public" // Corrected path
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
