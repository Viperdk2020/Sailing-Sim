
#include "SailSimSailPhysicsManager.h"
#include "SailSimPhysicsUtils.h"

using namespace SailSimPhysicsUtils;

void FSailSimSailPhysicsManager::Init(FRDGBuilder& Graph,
    uint32 V, FRDGBufferRef St,uint32 Ns, FRDGBufferRef Be,uint32 Nb,
    FRDGBufferRef S0,FRDGBufferRef S1,uint32 NsStrips)
{
    NumVerts=V;NumStretch=Ns;NumBend=Nb;NumStrips=NsStrips;
    StretchSRV=St;BendSRV=Be;Strip0SRV=S0;Strip1SRV=S1;

    Buffers = SailSimPhysicsUtils::CreatePerFrameBuffers(Graph, NumVerts);
    CachedPosSRV = Graph.CreateSRV(Buffers.Position);
}

void FSailSimSailPhysicsManager::Simulate(FRDGBuilder& G,float Dt)
{
    FRDGBufferRef ForceBuf = SailSimPhysicsUtils::CreateForceBuffer(G, NumVerts);
    Buffers.Forces = ForceBuf;

    SailSimPhysicsUtils::DispatchIntegrateHalf(G,Buffers,ForceBuf,Dt,NumVerts);
    SailSimPhysicsUtils::DispatchVLM(G,Buffers,Strip0SRV,Strip1SRV,NumStrips);

    for(int i=0;i<4;++i) SailSimPhysicsUtils::DispatchStretchSweep(G,Buffers,StretchSRV,NumStretch,Dt);
    for(int j=0;j<2;++j) SailSimPhysicsUtils::DispatchBendSweep(G,Buffers,BendSRV,NumBend,Dt);

    SailSimPhysicsUtils::DispatchIntegrateHalf(G,Buffers,ForceBuf,Dt,NumVerts);
}
