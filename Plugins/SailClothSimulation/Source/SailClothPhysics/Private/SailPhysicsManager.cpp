#include "SailPhysicsManager.h"
#include "GlobalShader.h"
#include "ShaderParameterUtils.h"
#include "RHICommandList.h"
#include "RenderGraphUtils.h"

#include "XPBDStretchCS.h"
#include "XPBDBendCS.h"
#include "VLMJacobiCS.h"

FSailPhysicsManager::FSailPhysicsManager() {}
FSailPhysicsManager::~FSailPhysicsManager() { Release(); }

void FSailPhysicsManager::Initialize(uint32 InVertexCount)
{
    VertexCount = InVertexCount;
    PositionsBuffer.Initialize(sizeof(FVector4f), VertexCount, BUF_UnorderedAccess | BUF_ShaderResource);
    VelocitiesBuffer.Initialize(sizeof(FVector4f), VertexCount, BUF_UnorderedAccess | BUF_ShaderResource);
    NormalsBuffer.Initialize(sizeof(FVector4f), VertexCount, BUF_UnorderedAccess | BUF_ShaderResource);
}

void FSailPhysicsManager::Release()
{
    PositionsBuffer.Release();
    VelocitiesBuffer.Release();
    NormalsBuffer.Release();
}

void FSailPhysicsManager::Tick(float DeltaTime)
{
    ENQUEUE_RENDER_COMMAND(SimulateCloth)(
        [this, DeltaTime](FRHICommandListImmediate& RHICmdList)
        {
            Simulate(RHICmdList, DeltaTime);
        }
    );
}

void FSailPhysicsManager::Simulate(FRHICommandListImmediate& RHICmdList, float DeltaTime)
{
    DispatchXPBDStretchCS(RHICmdList, DeltaTime);
    DispatchXPBDBendCS(RHICmdList, DeltaTime);
    DispatchVLMJacobiCS(RHICmdList, DeltaTime);
}

void FSailPhysicsManager::DispatchXPBDStretchCS(FRHICommandListImmediate& RHICmdList, float DeltaTime)
{
    TShaderMapRef<FXPBDStretchCS> ComputeShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));
    FXPBDStretchCS::FParameters Params;
    Params.Positions = PositionsBuffer.UAV;
    Params.Velocities = VelocitiesBuffer.UAV;
    Params.DeltaTime = DeltaTime;
    Params.VertexCount = VertexCount;
    int32 ThreadGroups = FMath::DivideAndRoundUp(VertexCount, 64);
    FComputeShaderUtils::Dispatch(RHICmdList, ComputeShader, Params, ThreadGroups, 1, 1);
}

void FSailPhysicsManager::DispatchXPBDBendCS(FRHICommandListImmediate& RHICmdList, float DeltaTime)
{
    TShaderMapRef<FXPBDBendCS> ComputeShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));
    FXPBDBendCS::FParameters Params;
    Params.Positions = PositionsBuffer.UAV;
    Params.Velocities = VelocitiesBuffer.UAV;
    Params.DeltaTime = DeltaTime;
    Params.VertexCount = VertexCount;
    int32 ThreadGroups = FMath::DivideAndRoundUp(VertexCount, 64);
    FComputeShaderUtils::Dispatch(RHICmdList, ComputeShader, Params, ThreadGroups, 1, 1);
}

void FSailPhysicsManager::DispatchVLMJacobiCS(FRHICommandListImmediate& RHICmdList, float DeltaTime)
{
    TShaderMapRef<FVLMJacobiCS> ComputeShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));
    FVLMJacobiCS::FParameters Params;
    Params.Positions = PositionsBuffer.UAV;
    Params.Velocities = VelocitiesBuffer.UAV;
    Params.DeltaTime = DeltaTime;
    Params.VertexCount = VertexCount;
    int32 ThreadGroups = FMath::DivideAndRoundUp(VertexCount, 64);
    FComputeShaderUtils::Dispatch(RHICmdList, ComputeShader, Params, ThreadGroups, 1, 1);
}