
#pragma once
#include "Modules/ModuleManager.h"

class FSailSimCoreModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
