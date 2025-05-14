using UnrealBuildTool;
public class SailClothRendering : ModuleRules {
    public SailClothRendering(ReadOnlyTargetRules Target) : base(Target) {
        PublicDependencyModuleNames.AddRange(new[] {
            "Core", "CoreUObject", "Engine", "RenderCore", "RHI", "RHICore", "RenderGraph", "ShaderCore", "SailClothPhysics"
        });
    }
}