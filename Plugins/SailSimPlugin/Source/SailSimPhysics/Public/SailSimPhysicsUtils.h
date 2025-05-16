
#pragma once
#include "CoreMinimal.h"
#include "RenderGraphResources.h"
#include "SailSimPhysicsTypes.h"

// Helper functions for SailSim physics RDG buffer handling
namespace SailSimPhysicsUtils
{
    /** Allocate position & velocity buffers or reuse cached ones */
    FSailSimBuffers CreatePerFrameBuffers(FRDGBuilder& GraphBuilder, uint32 NumVerts);

    /** Allocate a transient forces buffer */
    FRDGBufferRef CreateForceBuffer(FRDGBuilder& GraphBuilder, uint32 NumVerts);

    /** Compute thread group count for given element count */
    constexpr uint32 GroupCount(uint32 NumElements, uint32 GroupSize = 64)
    {
        return (NumElements + GroupSize - 1) / GroupSize;
    }
}
