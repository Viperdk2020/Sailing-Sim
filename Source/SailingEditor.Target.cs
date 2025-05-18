using UnrealBuildTool;
using System.Collections.Generic;

public class SailingEditorTarget : TargetRules
{
    public SailingEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
       // WindowsPlatform.Compiler = WindowsCompiler.Clang;

       

        DefaultBuildSettings = BuildSettingsVersion.Latest;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_6;
        ExtraModuleNames.AddRange(new string[] { "Sailing" });
    }
}
