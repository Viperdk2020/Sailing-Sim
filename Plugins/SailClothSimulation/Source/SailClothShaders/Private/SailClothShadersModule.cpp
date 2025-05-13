#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "ShaderCore.h"

class FSailClothShadersModule : public IModuleInterface
{
public:
  virtual void StartupModule() override
  {
    // e.g. map a shader directory exclusive to this module:
    FString ShaderPath = FPaths::Combine( IPluginManager::Get().FindPlugin("SailClothSimulation")->GetBaseDir(), TEXT("Shaders") );
    AddShaderSourceDirectoryMapping(TEXT("/Plugin/SailClothSimulation/Shaders"), ShaderPath);
  }
  virtual void ShutdownModule() override
  {
  //  RemoveShaderSourceDirectoryMapping(TEXT("/Plugin/SailClothSimulation/Shaders"));
  }
};

IMPLEMENT_MODULE(FSailClothShadersModule, SailClothShaders);
