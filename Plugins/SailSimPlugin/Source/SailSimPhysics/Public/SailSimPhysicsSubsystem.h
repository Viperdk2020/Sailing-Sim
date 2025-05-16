
#pragma once
#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "RenderGraphResources.h"
#include "SailSimPhysicsTypes.h"
#include "SailSimPhysicsSubsystem.generated.h"

/**
 * Engine subsystem that manages persistent double‑buffered GPU resources
 * and kicks the physics manager each frame on the async‑compute queue.
 */
UCLASS()
class USailSimPhysicsSubsystem : public UEngineSubsystem
   
{
    GENERATED_BODY()
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    virtual void Tick(float DeltaTime) ;
    //virtual bool IsTickable() const override { return true; }
    //virtual TStatId GetStatId() const override;
    virtual TStatId GetStatId() const ;

    

private:
    void SwapBuffers();

    // Double buffer indices
    uint8 ReadIdx = 0;
    uint8 WriteIdx = 1;

    FSailSimBuffers Buffers[2];
    uint32 NumVerts = 0;

    // External GPU fence
    FGPUFenceRHIRef SimulationFence;
};
