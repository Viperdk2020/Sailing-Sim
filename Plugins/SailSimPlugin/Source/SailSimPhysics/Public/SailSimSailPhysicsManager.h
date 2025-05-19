
#pragma once
#include "RenderGraphResources.h"
#include "SailSimPhysicsTypes.h"

/**
 * Per‑sail GPU simulation runner (buffers + dispatches)
 */
class FSailSimSailPhysicsManager
{
public:
    FSailSimSailPhysicsManager() = default;

    /** one‑time allocation after mesh cook */
    void Init(FRDGBuilder& GraphBuilder,
              uint32 InNumVerts,
              FRDGBufferRef InStretch,
              uint32 InNumStretch,
              FRDGBufferRef InBend,
              uint32 InNumBend,
              FRDGBufferRef InStrip0,
              FRDGBufferRef InStrip1,
              uint32 InNumStrips);

    /** build all passes (Integrate, VLM, XPBD) for this sail */
    void Simulate(FRDGBuilder& GraphBuilder, float DeltaTime);

    /** expose position SRV for rendering */
    FRDGBufferSRVRef GetPositionSRV() const { return CachedPosSRV; }

private:
    

  

    FSailSimBuffers Buffers;
    FRDGBufferSRVRef CachedPosSRV = nullptr;

    // immutable SRVs
    FRDGBufferRef StretchSRV = nullptr;
    FRDGBufferRef BendSRV    = nullptr;
    FRDGBufferRef Strip0SRV  = nullptr;
    FRDGBufferRef Strip1SRV  = nullptr;

    uint32 NumVerts   = 0;
    uint32 NumStretch = 0;
    uint32 NumBend    = 0;
    uint32 NumStrips  = 0;
};
