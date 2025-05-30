using UnrealBuildTool;
// Workaround for Clang Win64 missing kernel32 symbols
using System;
using System.IO;
public class SailSimRendering : ModuleRules
{
    public SailSimRendering(ReadOnlyTargetRules Target) : base(Target)
    {
       // Type = ModuleType.Runtime;
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "RenderCore",
            "RHI",
            "Projects",
            "Renderer"
        });
     

        PrivateDependencyModuleNames.AddRange(  new[] 
        { 
            "Renderer"

        });   // ← moved here

          // Use ModuleDirectory for relative include paths inside your module
        PublicIncludePaths.AddRange(new string[] {
            Path.Combine(ModuleDirectory, "Public")
        });

        PrivateIncludePaths.AddRange(new string[] {
            Path.Combine(ModuleDirectory, "Private")
        });


        // Compute the plugin root dir
      //  string PluginDir = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../"));

        // Add your “Shaders” folder to the *public* shader search path
      //  PublicAdditionalShaderDirectories.Add(Path.Combine(PluginDir, "Shaders"));
       
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
    }
}
