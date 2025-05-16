
#pragma once
#include "Modules/ModuleManager.h"

class FSailSimRenderingModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
