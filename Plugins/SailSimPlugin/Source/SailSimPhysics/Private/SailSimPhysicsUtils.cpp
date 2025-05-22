#include "SailSimPhysicsUtils.h"  
#include "RenderGraphBuilder.h"  
#include "RenderGraphUtils.h"
#include "RenderCore.h"  
#include "GlobalShader.h"  
#include "SailSimPhysicsTypes.h"  


// include kernel wrappers  
#include "Kernels/IntegrateHalfDTCS.h"  
#include "Kernels/XPBDStretchCS.h"  
#include "Kernels/XPBDBendCS.h"  
#include "Kernels/VLMJacobiCS.h"  

using namespace SailSimPhysicsUtils;  

// Buffer helpers (simplified)  
FSailSimBuffers SailSimPhysicsUtils::CreatePerFrameBuffers(FRDGBuilder& Graph, uint32 NumVerts)
{  
    FSailSimBuffers B;  
    FRDGBufferDesc Desc = FRDGBufferDesc::CreateStructuredDesc(sizeof(FSailSimVertex), NumVerts);  
    Desc.Usage |= BUF_UnorderedAccess;  
    B.Position = Graph.CreateBuffer(Desc, TEXT("SailSim.Pos"));  

    // Corrected: Use CreateStructuredDesc to define the buffer for FSailSimVelocity  
    Desc = FRDGBufferDesc::CreateStructuredDesc(sizeof(FSailSimVelocity), NumVerts);  
    Desc.Usage |= BUF_UnorderedAccess;  
    B.Velocity = Graph.CreateBuffer(Desc, TEXT("SailSim.Vel"));  

    return B;  
}

FRDGBufferRef SailSimPhysicsUtils::CreateForceBuffer(FRDGBuilder& Graph, uint32 NumVerts)
{  
    FRDGBufferDesc D = FRDGBufferDesc::CreateStructuredDesc(sizeof(int32), NumVerts*3);  
    D.Usage |= BUF_UnorderedAccess;  
    return Graph.CreateBuffer(D, TEXT("SailSim.Forces"));  
}

// --- Dispatches ---  
void SailSimPhysicsUtils::DispatchIntegrateHalf(FRDGBuilder& G, FSailSimBuffers B, FRDGBufferRef F,
                           float Dt, uint32 V)  
{  
    FIntegrateHalfDTCS::FParameters* P = G.AllocParameters<FIntegrateHalfDTCS::FParameters>();  
    P->Positions  = G.CreateUAV(B.Position);  
    P->Velocity   = G.CreateUAV(B.Velocity);  
    P->Forces     = G.CreateSRV(F);  
    P->DeltaTime  = Dt;  
    P->NumVerts   = V;  

    TShaderMapRef<FIntegrateHalfDTCS> CS(GetGlobalShaderMap(GMaxRHIFeatureLevel));  
    FComputeShaderUtils::AddPass(G, RDG_EVENT_NAME("IntegrateHalf"), CS, P,
                                 FIntVector(GroupCount(V),1,1));  
}  

void SailSimPhysicsUtils::DispatchStretchSweep(FRDGBuilder& G, FSailSimBuffers B, FRDGBufferRef Stretch,
                          uint32 N, float Dt)  
{  
    FXPBDStretchCS::FParameters* P = G.AllocParameters<FXPBDStretchCS::FParameters>();  
    P->Positions       = G.CreateUAV(B.Position);  
    P->Constraints     = G.CreateSRV(Stretch);  
    P->DeltaTime       = Dt;  
    P->NumConstraints  = N;  

    TShaderMapRef<FXPBDStretchCS> CS(GetGlobalShaderMap(GMaxRHIFeatureLevel));  
    FComputeShaderUtils::AddPass(G, RDG_EVENT_NAME("Stretch"), CS, P,  
                                 FIntVector(GroupCount(N),1,1));  
}  

void SailSimPhysicsUtils::DispatchBendSweep(FRDGBuilder& G, FSailSimBuffers B, FRDGBufferRef Bend,
                       uint32 N, float Dt)  
{  
    FXPBDBendCS::FParameters* P = G.AllocParameters<FXPBDBendCS::FParameters>();  
    P->Positions      = G.CreateUAV(B.Position);  
    P->BendData       = G.CreateSRV(Bend);  
    P->DeltaTime      = Dt;  
    P->NumConstraints = N;  

    TShaderMapRef<FXPBDBendCS> CS(GetGlobalShaderMap(GMaxRHIFeatureLevel));  
    FComputeShaderUtils::AddPass(G, RDG_EVENT_NAME("Bend"), CS, P,  
                                 FIntVector(GroupCount(N),1,1));  
}  

void SailSimPhysicsUtils::DispatchVLM(FRDGBuilder& G, FSailSimBuffers B, FRDGBufferRef S0, FRDGBufferRef S1,
                 uint32 N)  
{  
    FVLMJacobiCS::FParameters* P = G.AllocParameters<FVLMJacobiCS::FParameters>();  
    P->Positions      = G.CreateSRV(B.Position);  
    P->StripInfo0     = G.CreateSRV(S0);  
    P->StripInfo1     = G.CreateSRV(S1);  
    P->Forces         = G.CreateUAV(B.Forces ? B.Forces : G.RegisterExternalBuffer(nullptr));  
    P->NumConstraints = N;  

    TShaderMapRef<FVLMJacobiCS> CS(GetGlobalShaderMap(GMaxRHIFeatureLevel));  
    FComputeShaderUtils::AddPass(G, RDG_EVENT_NAME("VLM"), CS, P,  
                                 FIntVector(GroupCount(N),1,1));  
}

