
#pragma once
#include "RenderGraphResources.h"
#include "RenderGraphBuilder.h"
#include "RHICommandList.h"
#include "SailSimPhysicsTypes.h"

namespace SailSimPhysicsUtils
{
    // Buffer helpers
    FSailSimBuffers CreatePerFrameBuffers(FRDGBuilder&, uint32 NumVerts);
    FRDGBufferRef   CreateForceBuffer    (FRDGBuilder&, uint32 NumVerts);

    // --- Direct shader dispatches (stand‑alone) ---
    void DispatchIntegrateHalf(FRDGBuilder&, FSailSimBuffers, FRDGBufferRef Forces,
                               float DeltaTime, uint32 NumVerts);

    void DispatchStretchSweep(FRDGBuilder&, FSailSimBuffers,
                              FRDGBufferRef StretchConstraints,
                              uint32 NumConstraints, float DeltaTime);

    void DispatchBendSweep(FRDGBuilder&, FSailSimBuffers,
                           FRDGBufferRef BendConstraints,
                           uint32 NumConstraints, float DeltaTime);

    void DispatchVLM(FRDGBuilder&, FSailSimBuffers,
                     FRDGBufferRef StripInfo0, FRDGBufferRef StripInfo1,
                     uint32 NumStrips);

    inline uint32 GroupCount(uint32 N, uint32 G=64) { return (N+G-1)/G; }
}
