
#include "SailSimRenderingModule.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"
#include "ShaderCore.h" 

#define LOCTEXT_NAMESPACE "FSailSimRenderingModule"

void FSailSimRenderingModule::StartupModule()
{
    // Find where the plugin is installed on disk
    FString PluginBaseDir = IPluginManager::Get().FindPlugin("SailSimPlugin")->GetBaseDir();

    // This folder should contain your .usf/.ush files
    FString ShaderDir = FPaths::Combine(PluginBaseDir, TEXT("Shaders"));

    // Map the virtual path "/Plugin/MyPlugin" → real disk path
    AddShaderSourceDirectoryMapping(TEXT("/Plugin/SailSimPlugin"), ShaderDir);
}

void FSailSimRenderingModule::ShutdownModule()
{
    // Module shutdown logic
}

#undef LOCTEXT_NAMESPACE
IMPLEMENT_MODULE(FSailSimRenderingModule, SailSimRendering);
