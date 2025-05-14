#include "SailPhysicsManager.h"
#include "ShaderParameterUtils.h"
#include "GlobalShader.h"
#include "PipelineStateCache.h"
#include "RenderGraphBuilder.h"
#include "SailPhysicsUtils.h"

// Include our kernel wrapper
#include "Kernels/XPBDStretchCS.h"

FSailPhysicsManager& FSailPhysicsManager::Get()
{
    static FSailPhysicsManager Instance;
    return Instance;
}

void FSailPhysicsManager::Init()
{
    // Pre-cache shaders if necessary
}

void FSailPhysicsManager::Release()
{
    ShaderMapCache.Empty();
}

void FSailPhysicsManager::SolveStretch(
    FRDGBuilder& GraphBuilder,
    FRDGBufferRef PositionBuffer,
    FRDGBufferRef ConstraintBuffer,
    uint32 NumVerts,
    uint32 NumConstraints,
    uint32 Iterations
)
{
    FXPBDStretchCS::FParameters* Params = GraphBuilder.AllocParameters<FXPBDStretchCS::FParameters>();
    Params->Positions = GraphBuilder.CreateSRV(PositionBuffer);
    Params->Constraints = GraphBuilder.CreateSRV(ConstraintBuffer);
    Params->OutPositions = GraphBuilder.CreateUAV(PositionBuffer);
    Params->NumVerts = NumVerts;
    Params->NumConstraints = NumConstraints;

    for (uint32 Iter = 0; Iter < Iterations; ++Iter)
    {
        TShaderMapRef<FXPBDStretchCS> ComputeShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));
        FComputeShaderUtils::AddPass(
            GraphBuilder,
            RDG_EVENT_NAME("XPBDStretch Iter %d", Iter),
            ComputeShader,
            Params,
            FIntVector(FMath::DivideAndRoundUp(NumConstraints, 64), 1, 1)
        );
    }
}
