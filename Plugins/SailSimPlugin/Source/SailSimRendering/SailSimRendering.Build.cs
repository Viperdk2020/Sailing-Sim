using UnrealBuildTool;

public class SailSimRendering : ModuleRules
{
    public SailSimRendering(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[] {
                "D:\\UE5\\Unreal Projects\\Sailing\\Plugins\\SailSimPlugin\\Source\\SailSimRendering\\Public"
            }
        );

        PrivateIncludePaths.AddRange(
            new string[] {
                "D:\\UE5\\Unreal Projects\\Sailing\\Plugins\\SailSimPlugin\\Source\\SailSimRendering\\Private",
                "D:\\UE5\\Unreal Projects\\Sailing\\Plugins\\SailSimPlugin\\Source\\SailSimRendering\\Public"
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
