#include "SailPhysicsManager.h"
#include "GlobalShader.h"
#include "ShaderParameterUtils.h"
#include "RenderGraphUtils.h"
#include "RenderGraphBuilder.h"

#include "XPBDStretchCS.h"
#include "XPBDBendCS.h"
#include "VLMJacobiCS.h"

FSailPhysicsManager::FSailPhysicsManager() = default;

FSailPhysicsManager::~FSailPhysicsManager()
{
    Release();
}

void FSailPhysicsManager::Initialize(uint32 InVertexCount)
{
    Release();
    if (InVertexCount == 0)
        return;
    VertexCount = InVertexCount;

    PositionsBuffer.Initialize(VertexCount, sizeof(FVector4f), TEXT("SailPositionsBuffer"));
    VelocitiesBuffer.Initialize(VertexCount, sizeof(FVector4f), TEXT("SailVelocitiesBuffer"));
    NormalsBuffer.Initialize(VertexCount, sizeof(FVector4f), TEXT("SailNormalsBuffer"));
}

void FSailPhysicsManager::Release()
{
    PositionsBuffer.Release();
    VelocitiesBuffer.Release();
    NormalsBuffer.Release();
    VertexCount = 0;
}

void FSailPhysicsManager::Simulate(FRHICommandListImmediate& RHICmdList, float DeltaTime)
{
    if (VertexCount == 0)
        return;

    FRDGBuilder GraphBuilder(RHICmdList);
    //RENDERCORE_API::FRDGBufferPool; //SetExternalBufferAccess(, ERDGResourceState::CopySource);
    FRDGBufferRef PositionsRDG  = GraphBuilder.RegisterExternalBuffer(PositionsBuffer.);
    FRDGBufferRef VelocitiesRDG = GraphBuilder.RegisterExternalBuffer(VelocitiesBuffer.Buffer);
    FRDGBufferRef NormalsRDG    = GraphBuilder.RegisterExternalBuffer(NormalsBuffer.Buffer);

    DispatchXPBDStretchCS(GraphBuilder, DeltaTime);
    DispatchXPBDBendCS(GraphBuilder, DeltaTime);
    DispatchVLMJacobiCS(GraphBuilder, DeltaTime);

    GraphBuilder.Execute();
}

void FSailPhysicsManager::DispatchXPBDStretchCS(FRDGBuilder& GraphBuilder, float DeltaTime)
{
    TShaderMapRef<FXPBDStretchCS> ComputeShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));
    FXPBDStretchCS::FParameters* Params = GraphBuilder.AllocParameters<FXPBDStretchCS::FParameters>();

    FRDGBufferRef PositionsRDG  = GraphBuilder.RegisterExternalBuffer(PositionsBuffer.Buffer);
    FRDGBufferRef VelocitiesRDG = GraphBuilder.RegisterExternalBuffer(VelocitiesBuffer.Buffer);

    Params->Positions    = GraphBuilder.CreateSRV(PositionsRDG, PF_A32B32G32R32F);
    Params->Velocities   = GraphBuilder.CreateSRV(VelocitiesRDG, PF_A32B32G32R32F);
    Params->OutPositions = GraphBuilder.CreateUAV(PositionsRDG, PF_A32B32G32R32F);

    Params->DeltaTime    = DeltaTime;
    Params->VertexCount  = VertexCount;

    int32 ThreadGroups = FMath::DivideAndRoundUp<int32>(VertexCount, GroupSize);

    FComputeShaderUtils::AddPass(
        GraphBuilder,
        RDG_EVENT_NAME("XPBDStretchCS"),
        ComputeShader,
        Params,
        FIntVector(ThreadGroups, 1, 1)
    );
}

void FSailPhysicsManager::DispatchXPBDBendCS(FRDGBuilder& GraphBuilder, float DeltaTime)
{
    TShaderMapRef<FXPBDBendCS> ComputeShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));
    FXPBDBendCS::FParameters* Params = GraphBuilder.AllocParameters<FXPBDBendCS::FParameters>();

    FRDGBufferRef PositionsRDG  = GraphBuilder.RegisterExternalBuffer(PositionsBuffer.Buffer);
    FRDGBufferRef VelocitiesRDG = GraphBuilder.RegisterExternalBuffer(VelocitiesBuffer.Buffer);

    Params->Positions     = GraphBuilder.CreateSRV(PositionsRDG, PF_A32B32G32R32F);
    Params->Velocities    = GraphBuilder.CreateSRV(VelocitiesRDG, PF_A32B32G32R32F);
    Params->OutPositions  = GraphBuilder.CreateUAV(PositionsRDG, PF_A32B32G32R32F);
    Params->OutVelocities = GraphBuilder.CreateUAV(VelocitiesRDG, PF_A32B32G32R32F);

    Params->BendStiffness = 0.0f;
    Params->DeltaTime     = DeltaTime;
    Params->VertexCount   = VertexCount;

    int32 ThreadGroups = FMath::DivideAndRoundUp<int32>(VertexCount, GroupSize);

    FComputeShaderUtils::AddPass(
        GraphBuilder,
        RDG_EVENT_NAME("XPBDBendCS"),
        ComputeShader,
        Params,
        FIntVector(ThreadGroups, 1, 1)
    );
}

void FSailPhysicsManager::DispatchVLMJacobiCS(FRDGBuilder& GraphBuilder, float DeltaTime)
{
    TShaderMapRef<FVLMJacobiCS> ComputeShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));
    FVLMJacobiCS::FParameters* Params = GraphBuilder.AllocParameters<FVLMJacobiCS::FParameters>();

    FRDGBufferRef PositionsRDG  = GraphBuilder.RegisterExternalBuffer(PositionsBuffer.Buffer);
    FRDGBufferRef VelocitiesRDG = GraphBuilder.RegisterExternalBuffer(VelocitiesBuffer.Buffer);

    Params->CurrentVorticity = GraphBuilder.CreateSRV(PositionsRDG, PF_A32B32G32R32F);
    Params->VelocityField    = GraphBuilder.CreateSRV(VelocitiesRDG, PF_A32B32G32R32F);
    Params->OutVorticity     = GraphBuilder.CreateUAV(PositionsRDG, PF_A32B32G32R32F);

    Params->RelaxationFactor = 0.0f;
    Params->DeltaTime        = DeltaTime;
    Params->VertexCount      = VertexCount;

    int32 ThreadGroups = FMath::DivideAndRoundUp<int32>(VertexCount, GroupSize);

    FComputeShaderUtils::AddPass(
        GraphBuilder,
        RDG_EVENT_NAME("VLMJacobiCS"),
        ComputeShader,
        Params,
        FIntVector(ThreadGroups, 1, 1)
    );
}