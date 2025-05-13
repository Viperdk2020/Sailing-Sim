// SailClothSimulationModule.cpp

#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "ShaderCore.h"            // for AddShaderSourceDirectoryMapping

class FSailClothSimulationModule : public IModuleInterface
{
public:
    virtual void StartupModule() override
    {
        // Register our plugin's Shaders folder under the virtual path "/Plugin/SailClothSimulation"
       
        /*FString PluginBaseDir = IPluginManager::Get().FindPlugin("SailClothSimulation")->GetBaseDir();
        FString ShaderDir = FPaths::Combine(PluginBaseDir, TEXT("Shaders"));
        AddShaderSourceDirectoryMapping(TEXT("/Plugin/SailClothSimulation/Shaders"), ShaderDir);
        */
    }

    virtual void ShutdownModule() override
    {
        // (Optional) if you want to remove the mapping on shutdown:
      //  RemoveShaderSourceDirectoryMapping(TEXT("/Plugin/SailClothSimulation"));
    }
};

IMPLEMENT_MODULE(FSailClothSimulationModule, SailClothSimulation);
