
#pragma once
#include "CoreMinimal.h"
#include "RenderGraphResources.h"
#include "SailSimPhysicsTypes.h"

/**
 * Singleton access to sail simulation GPU passes.
 */
class SAILSIMPHYSICS_API FSailSimPhysicsManager
{
public:
    static FSailSimPhysicsManager& Get();


	int32 GBendIterations = 1;

    void Init();
    void Release();

    /** Dispatch integrate half-dt pass (render thread only) */
    void DispatchIntegrateHalf(
        FRDGBuilder& GraphBuilder,
        FSailSimBuffers Buffers,
        FRDGBufferRef  Forces,
        float DeltaTime,
        uint32 NumVerts);


/** Single XPBD stretch sweep */
void DispatchStretchSweep(
    FRDGBuilder& GraphBuilder,
    FSailSimBuffers Buffers,
    FRDGBufferRef  StretchConstraints,
    uint32 NumConstraints,
    float DeltaTime);


/** Single XPBD bend sweep */
void DispatchBendSweep(
    FRDGBuilder& GraphBuilder,
    FSailSimBuffers Buffers,
    FRDGBufferRef BendConstraints,
    uint32 NumConstraints,
    float DeltaTime);


/** High-level frame simulation: runs multiple substeps entirely on GPU */
void SimulateFrame(
    FRDGBuilder& GraphBuilder,
    FSailSimBuffers Buffers,
    FRDGBufferRef StretchConstraints,
    uint32 NumStretch,
    FRDGBufferRef BendConstraints,
    uint32 NumBend,
    uint32 NumVerts,
    float DeltaTime);


/** Compute aerodynamic forces using VLM */
void DispatchVLM(
    FRDGBuilder& GraphBuilder,
    FSailSimBuffers Buffers,
    FRDGBufferRef StripInfo0,
    FRDGBufferRef StripInfo1,
    uint32 NumStrips);

private:
    FSailSimPhysicsManager() = default;
};
