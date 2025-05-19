
#include "SailSimSailPhysicsManager.h"
#include "SailSimPhysicsUtils.h"
#include "SailSimPhysicsManager.h"

// Include compute kernel wrappers
#include "Kernels/IntegrateHalfDTCS.h"
#include "Kernels/VLMJacobiCS.h"
#include "Kernels/XPBDStretchCS.h"
#include "Kernels/XPBDBendCS.h"



void FSailSimSailPhysicsManager::Init(FRDGBuilder& Graph,
                                      uint32 InVerts,
                                      FRDGBufferRef InStretch, uint32 InNumStretch,
                                      FRDGBufferRef InBend,    uint32 InNumBend,
                                      FRDGBufferRef InStrip0,  FRDGBufferRef InStrip1,
                                      uint32 InNumStrips)
{
    NumVerts = InVerts;
    NumStretch = InNumStretch;
    NumBend = InNumBend;
    NumStrips = InNumStrips;

    StretchSRV = InStretch;
    BendSRV    = InBend;
    Strip0SRV  = InStrip0;
    Strip1SRV  = InStrip1;

    Buffers = SailSimPhysicsUtils::CreatePerFrameBuffers(Graph, NumVerts);
    CachedPosSRV = Graph.CreateSRV(Buffers.Position);

    // register with boat‑level manager
    FSailSimPhysicsManager::Get().AddSail(this);
}

void FSailSimSailPhysicsManager::Simulate(FRDGBuilder& Graph, float Dt)
{
    // allocate per‑substep force buffer
    FRDGBufferRef ForceBuf = SailSimPhysicsUtils::CreateForceBuffer(Graph, NumVerts);

    // integrate half DT
    SailSimPhysicsUtils::DispatchIntegrateHalf(Graph, Buffers, ForceBuf, Dt, NumVerts);

    // VLM Jacobi
    FSailSimPhysicsUtils::DispatchVLM(Graph, Buffers, Strip0SRV, Strip1SRV, NumStrips);

    // stretch sweeps
    for(int i=0;i<4;++i)
        FSailSimPhysicsUtils::DispatchStretchSweep(Graph, Buffers, StretchSRV, NumStretch, Dt);

    // bend sweeps
    for(int j=0;j<2;++j)
        FSailSimPhysicsUtils::DispatchBendSweep(Graph, Buffers, BendSRV, NumBend, Dt);

    // second integrate
    FSailSimPhysicsUtils::DispatchIntegrateHalf(Graph, Buffers, ForceBuf, Dt, NumVerts);
}
