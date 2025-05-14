using UnrealBuildTool;
using System.IO;
public class SailClothPhysics : ModuleRules {
    public SailClothPhysics(ReadOnlyTargetRules Target) : base(Target) {
        PublicDependencyModuleNames.AddRange(new[] {
            "Core", "CoreUObject", "Engine", "RenderCore", "RHI", "RHICore", "RenderGraph", "ShaderCore"
        });
        AdditionalShaderDirectories.Add(Path.Combine(ModuleDirectory, "../../Shaders"));
    }
}