
#pragma once
#include "Modules/ModuleManager.h"

class FSailSimPhysicsModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
