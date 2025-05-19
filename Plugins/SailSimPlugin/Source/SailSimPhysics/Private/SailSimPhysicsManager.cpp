#pragma once

#include "SailSimPhysicsManager.h"
#include "SailSimSailPhyiscsManager.h"







///////////// Cvars for tuning simulation ////////////////
static int32 GSimSubsteps = 4;
static FAutoConsoleVariableRef CVarSimSubsteps(
    TEXT("s.Sail.Substeps"),
    GSimSubsteps,
    TEXT("Number of physics substeps per frame"),
    ECVF_Default);
static int32 GStretchIterations = 4;
static FAutoConsoleVariableRef CVarStretchIter(
    TEXT("s.Sail.StretchIterations"),
    GStretchIterations,
    TEXT("Number of XPBD stretch sweeps per substep"),
    ECVF_Default);

////////

FSailSimPhysicsManager& FSailSimPhysicsManager::Get()
{
 //   static FSailSimPhysicsManager Instance;
    return NULL;
}



void FSailSimPhysicsManager::Init()
{
    // Compile permutation overrides, pre-allocate UAVs, etc.
}

void FSailSimPhysicsManager::Release()
{
    // Destroy any RHIs or UAV pools you allocated
}



void FSailSimPhysicsManager::SimulateFrame(float DeltaTime)
{
   // FRDGBuilder& GraphBuilder;
    DispatchData.Buffers;
   // FSailSimBuffers Buffers;
   // FRDGBufferRef StretchConstraints;


  //  uint32 NumStretch;
 //   FRDGBufferRef BendConstraints;
 //   uint32 NumBend;
  //  uint32 NumVerts;
        ///Graph,
         //   Buffers[WriteIdx],
          //  StretchConstraintBuffer, NumStretch,
          //  BendConstraintBuffer, NumBend,
          //  NumVerts,





        const float SubDt = DeltaTime / float(GSimSubsteps);

    for (int32 Step = 0; Step < GSimSubsteps; ++Step)
    {
        // Allocate a transient force buffer (currently zero; VLM will fill later)
       // FRDGBufferRef ForceBuf = SailSimPhysicsUtils::CreateForceBuffer(GraphBuilder, NumVerts);

        // First half-step integrate
      //  DispatchIntegrateHalf(GraphBuilder, Buffers, ForceBuf, SubDt, NumVerts);

        // Stretch sweeps
        for (int32 i = 0; i < GStretchIterations; ++i)
        {
           // DispatchStretchSweep(GraphBuilder, Buffers, StretchConstraints, NumStretch, SubDt);
        }

        // Bend sweeps
        for (int32 j = 0; j < GBendIterations; ++j)
        {
         //   DispatchBendSweep(GraphBuilder, Buffers, BendConstraints, NumBend, SubDt);
        }

        // Second half-step integrate (reuse same forces)
       // DispatchIntegrateHalf(GraphBuilder, Buffers, ForceBuf, SubDt, NumVerts);
    }
}








//////////////////////////////// ShaderStuff /////////////////////////////////

void FSailSimPhysicsManager::DispatchIntegrateHalf(
    FRDGBuilder& GraphBuilder,
    FSailSimBuffers Buffers,
    FRDGBufferRef  Forces,
    float DeltaTime,
    uint32 NumVerts)
{
    FIntegrateHalfDTCS::FParameters* Params = GraphBuilder.AllocParameters<FIntegrateHalfDTCS::FParameters>();
    Params->Positions = GraphBuilder.CreateUAV(Buffers.Position);
    Params->Velocity  = GraphBuilder.CreateUAV(Buffers.Velocity);
    Params->Forces    = GraphBuilder.CreateSRV(Forces);
    Params->DeltaTime = DeltaTime;
    Params->NumVerts  = NumVerts;

    TShaderMapRef<FIntegrateHalfDTCS> ComputeShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));
    FComputeShaderUtils::AddPass(
        GraphBuilder,
        RDG_EVENT_NAME("IntegrateHalfDT"),
        ComputeShader,
        Params,
        FIntVector(SailSimPhysicsUtils::GroupCount(NumVerts), 1, 1));
}

void FSailSimPhysicsManager::DispatchStretchSweep(
    FRDGBuilder& GraphBuilder,
    FSailSimBuffers Buffers,
    FRDGBufferRef StretchConstraints,
    uint32 NumConstraints,
    float DeltaTime)
{
    FXPBDStretchCS::FParameters* Params = GraphBuilder.AllocParameters<FXPBDStretchCS::FParameters>();
    Params->Positions       = GraphBuilder.CreateUAV(Buffers.Position);
    Params->Constraints     = GraphBuilder.CreateSRV(StretchConstraints);
    Params->DeltaTime       = DeltaTime;
    Params->NumConstraints  = NumConstraints;

    TShaderMapRef<FXPBDStretchCS> CS(GetGlobalShaderMap(GMaxRHIFeatureLevel));
    FComputeShaderUtils::AddPass(
        GraphBuilder,
        RDG_EVENT_NAME("XPBDStretchSweep"),
        CS,
        Params,
        FIntVector(SailSimPhysicsUtils::GroupCount(NumConstraints), 1, 1));
}

void FSailSimPhysicsManager::DispatchBendSweep(
    FRDGBuilder& GraphBuilder,
    FSailSimBuffers Buffers,
    FRDGBufferRef BendConstraints,
    uint32 NumConstraints,
    float DeltaTime)
{
    FXPBDBendCS::FParameters* Params = GraphBuilder.AllocParameters<FXPBDBendCS::FParameters>();
    Params->Positions      = GraphBuilder.CreateUAV(Buffers.Position);
    Params->BendData       = GraphBuilder.CreateSRV(BendConstraints);
    Params->DeltaTime      = DeltaTime;
    Params->NumConstraints = NumConstraints;

    TShaderMapRef<FXPBDBendCS> CS(GetGlobalShaderMap(GMaxRHIFeatureLevel));
    FComputeShaderUtils::AddPass(
        GraphBuilder,
        RDG_EVENT_NAME("XPBDBendSweep"),
        CS,
        Params,
        FIntVector(SailSimPhysicsUtils::GroupCount(NumConstraints), 1, 1));
}






void FSailSimPhysicsManager::DispatchVLM(
    FRDGBuilder& GraphBuilder,
    FSailSimBuffers Buffers,
    FRDGBufferRef StripInfo0,
    FRDGBufferRef StripInfo1,
    uint32 NumStrips)
{
    FVLMJacobiCS::FParameters* Params = GraphBuilder.AllocParameters<FVLMJacobiCS::FParameters>();
    Params->Positions    = GraphBuilder.CreateSRV(Buffers.Position);
    Params->StripInfo0   = GraphBuilder.CreateSRV(StripInfo0);
    Params->StripInfo1   = GraphBuilder.CreateSRV(StripInfo1);
    Params->Forces       = GraphBuilder.CreateUAV(Buffers.Forces);
    Params->NumConstraints = NumStrips;

    TShaderMapRef<FVLMJacobiCS> CS(GetGlobalShaderMap(GMaxRHIFeatureLevel));
    FComputeShaderUtils::AddPass(
        GraphBuilder,
        RDG_EVENT_NAME("VLMJacobi"),
        CS,
        Params,
        FIntVector(SailSimPhysicsUtils::GroupCount(NumStrips), 1, 1));
}
