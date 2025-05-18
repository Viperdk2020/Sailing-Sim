using UnrealBuildTool;
using System.Collections.Generic;

public class SailingTarget : TargetRules
{
    public SailingTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        //WindowsPlatform.Compiler = WindowsCompiler.;



        DefaultBuildSettings = BuildSettingsVersion.Latest;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_6;
        ExtraModuleNames.AddRange(new string[] { "Sailing" });
    }
}
