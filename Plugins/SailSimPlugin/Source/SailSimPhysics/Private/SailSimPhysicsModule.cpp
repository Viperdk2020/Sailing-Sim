
#include "SailSimPhysicsModule.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FSailSimPhysicsModule"

void FSailSimPhysicsModule::StartupModule()
{
    TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("SailSimPlugin"));
    if (Plugin.IsValid())
    {
        FString PluginShaderDir = FPaths::Combine(Plugin->GetBaseDir(), TEXT("Shaders"));
        AddShaderSourceDirectoryMapping(TEXT("/SailSimPlugin"), PluginShaderDir);
        UE_LOG(LogTemp, Log, TEXT("Registered /SailSimPlugin shader dir: %s"), *PluginShaderDir);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Could not find SailSimCore for shader mapping!"));
    }
}

void FSailSimPhysicsModule::ShutdownModule()
{
    // Module shutdown logic
}

#undef LOCTEXT_NAMESPACE
IMPLEMENT_MODULE(FSailSimPhysicsModule, SailSimPhysics);
