#include "SailSimRenderDebug.h"

#include "Runtime/Renderer/Private/SceneRendering.h"   // brings in FViewInfo
#include "RenderGraphBuilder.h"
#include "SceneView.h"
#include "ScreenPass.h"
#include "RenderGraphUtils.h"         // AddComputeShaderPass, AddScreenPass
#include "ShaderParameterUtils.h"
#include "GlobalShader.h"
#include "ShaderCore.h"
#include "RenderCore.h"

// Define FStretchCS compute shader so that its parameters are available.
class FStretchCS : public FGlobalShader
{
    DECLARE_GLOBAL_SHADER(FStretchCS);
    SHADER_USE_PARAMETER_STRUCT(FStretchCS, FGlobalShader);

    BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
        SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<float4>, Positions)
        SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<uint2>, Pairs)
        SHADER_PARAMETER_UAV(FRDGTextureUAVRef, OutDebug)
        SHADER_PARAMETER(FMatrix44f, ViewProj)
        SHADER_PARAMETER(uint32, NumPairs)
        SHADER_PARAMETER(float, ErrorScale)
    END_SHADER_PARAMETER_STRUCT()
};

IMPLEMENT_GLOBAL_SHADER(FStretchCS, "/Plugin/SailSimPlugin/Shaders/SailStretchDebugCS.usf", "MainCS", SF_Compute);

// Define FDebugCompositePS pixel shader.
class FDebugCompositePS : public FGlobalShader
{
    DECLARE_GLOBAL_SHADER(FDebugCompositePS);
    SHADER_USE_PARAMETER_STRUCT(FDebugCompositePS, FGlobalShader);

    BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
        SHADER_PARAMETER_RDG_TEXTURE(Texture2D, DebugTexture)
        SHADER_PARAMETER_SAMPLER(SamplerState, DebugTextureSampler)
    END_SHADER_PARAMETER_STRUCT()
};

IMPLEMENT_GLOBAL_SHADER(FDebugCompositePS, "/Plugin/SailSimPlugin/Shaders/SailStretchDebugCS.usf", "MainPS", SF_Pixel);

bool FSailSimRenderDebug::IsEnabled()
{
   // return CVarSailGPUDebug.GetValueOnAnyThread() != 0;
}

FRDGTextureRef FSailSimRenderDebug::GetOrCreateDebugTarget(FRDGBuilder& Graph, const FViewInfo& View)
{
    FRDGTextureDesc Desc = FRDGTextureDesc::Create2D
    (
       View.ViewRect.Size(),
        PF_R8G8B8A8,
        FClearValueBinding::Black,
        TexCreate_ShaderResource | TexCreate_UAV | TexCreate_RenderTargetable
    );

    TShaderMapRef<FStretchCS> StretchCS(View.ShaderMap);

   


    return Graph.CreateTexture(Desc, TEXT("Sail.DebugRT"));
}

void FSailSimRenderDebug::AddGPUStretchDebug(
    FRDGBuilder& Graph,
    FRDGBufferSRVRef PosSRV,
    FRDGBufferSRVRef PairSRV,
    uint32 NumPairs,
    const FViewInfo& View)
{
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
    if (!IsEnabled())
    {
        return;
    }

    // 1) Allocate and clear our debug render target
    FRDGTextureRef DebugRT = GetOrCreateDebugTarget(Graph, View);
    AddClearUAVPass(Graph, Graph.CreateUAV(DebugRT), FUintVector4(0, 0, 0, 0));

    // 2) Prepare parameters for the stretch compute shader
    FStretchCS::FParameters* Params = Graph.AllocParameters<FStretchCS::FParameters>();
    Params->Positions = PosSRV;
    Params->Pairs = PairSRV;
    Params->OutDebug = Graph.CreateUAV(DebugRT);
    Params->ViewProj = FMatrix44f(View.ViewMatrices.GetViewProjectionMatrix());
    Params->NumPairs = NumPairs;
    Params->ErrorScale = 10.0f;

    // 3) Dispatch the compute shader
    TShaderMapRef<FStretchCS> StretchCS(View.ShaderMap, FStretchCS::FPermutationDomain());
    const uint32 GroupCountX = FMath::DivideAndRoundUp(NumPairs, 64u);
    FComputeShaderUtils::AddPass(
        Graph,
        RDG_EVENT_NAME("SailStretchGPU"),
        ERDGPassFlags::Compute,
        *StretchCS.GetComputeShader(),
        Params,
        FIntVector(GroupCountX, 1, 1)
    );

    // 4) Composite the debug RT over the scene color
    const FSceneTextures& SceneTextures = FSceneTextures::Get(Graph);
    FRDGTextureRef SceneColor = SceneTextures.Color.Target;

    TShaderMapRef<FScreenPassVS> ScreenVS(View.ShaderMap, FScreenPassVS::FPermutationDomain());
    TShaderMapRef<FDebugCompositePS> CompositePS(View.ShaderMap, FDebugCompositePS::FPermutationDomain());

    AddScreenPass(
        Graph,
        View,
        SceneColor,
        DebugRT,
        *ScreenVS,
        *CompositePS
    );
#endif
}