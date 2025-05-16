
#include "SailSimPhysicsUtils.h"
#include "RenderGraphBuilder.h"

using namespace SailSimPhysicsUtils;

FSailSimBuffers SailSimPhysicsUtils::CreatePerFrameBuffers(FRDGBuilder& GraphBuilder, uint32 NumVerts)
{
    FSailSimBuffers Buffers;

    FRDGBufferDesc PosDesc = FRDGBufferDesc::CreateStructuredDesc(sizeof(FSailSimVertex), NumVerts);
    PosDesc.Usage |= BUF_UnorderedAccess;
    Buffers.Position = GraphBuilder.CreateBuffer(PosDesc, TEXT("SailSim.Position"));

    FRDGBufferDesc VelDesc = FRDGBufferDesc::CreateStructuredDesc(sizeof(FSailSimVelocity), NumVerts);
    VelDesc.Usage |= BUF_UnorderedAccess;
    Buffers.Velocity = GraphBuilder.CreateBuffer(VelDesc, TEXT("SailSim.Velocity"));

    return Buffers;
}

FRDGBufferRef SailSimPhysicsUtils::CreateForceBuffer(FRDGBuilder& GraphBuilder, uint32 NumVerts)
{
    FRDGBufferDesc ForceDesc = FRDGBufferDesc::CreateStructuredDesc(sizeof(FSailSimForce), NumVerts);
    ForceDesc.Usage |= BUF_UnorderedAccess;
    return GraphBuilder.CreateBuffer(ForceDesc, TEXT("SailSim.Forces"));
}
