using UnrealBuildTool;
using System.IO;
using UnrealBuildTool.Rules;

public class SailClothSimulation : ModuleRules
{
    public SailClothSimulation(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
        PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "RenderCore",  // <--- implements FRHIResource::MarkForDelete
            "RHI",          // <--- for FRWBufferStructured, SRV/UAV APIs
            "ProceduralMeshComponent",
            "SailClothShaders"  // <-- our new shader helper module
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
