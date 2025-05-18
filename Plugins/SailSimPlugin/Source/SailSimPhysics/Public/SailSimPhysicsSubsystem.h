
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
    virtual bool IsTickable() const override { return bEnabled; }
    virtual void Tick(float DeltaTime) ;
    //virtual bool IsTickable() const override { return true; }
    //virtual TStatId GetStatId() const override;
    virtual TStatId GetStatId() const ;

    /** Register a sail component (called from the component’s BeginPlay) */
    void RegisterCloth(class USailClothComponent* Comp);

private:
    void SwapBuffers();

    void CreateBuffers(uint32 NumVerts);
    void KickSim(FRDGBuilder& GraphBuilder, float Dt);

    /** double-buffered GPU resources */
    FSailSimBuffers Buffers[2];
    uint8 ReadIdx = 0;
    uint8 WriteIdx = 1;

    /** number of vertices in the current simulation */
    uint32 NumVerts = 0;

    /** cross-frame GPU fence */
    FGPUFenceRHIRef Fence;

    bool bEnabled = false;

    // Double buffer indices
    
    // External GPU fence
    FGPUFenceRHIRef SimulationFence;
};
