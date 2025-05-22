
#pragma once
#include "Subsystems/EngineSubsystem.h"
#include "SailSimPhysicsSubsystem.generated.h"

class FSailSimPhysicsManager;

UCLASS()
class SAILSIMPHYSICS_API USailSimPhysicsSubsystem : public UEngineSubsystem
{
    GENERATED_BODY()
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    virtual void Tick(float DeltaSeconds);
   // virtual bool IsTickable() const override { return true; }
    virtual TStatId GetStatId() const;

private:
    FSailSimPhysicsManager* Manager = nullptr;
    FGPUFenceRHIRef Fence;
};
