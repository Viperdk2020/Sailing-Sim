using UnrealBuildTool;
public class SailCloth : ModuleRules {
    public SailCloth(ReadOnlyTargetRules Target) : base(Target) {
        PublicDependencyModuleNames.AddRange(new[] { "Core", "CoreUObject", "Engine" });
        PrivateDependencyModuleNames.Add("SailClothPhysics");
    }
}