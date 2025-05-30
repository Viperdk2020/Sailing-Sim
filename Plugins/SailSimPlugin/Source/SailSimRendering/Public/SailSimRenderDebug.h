
#pragma once
#include "RenderGraphBuilder.h"
#include  "ScreenPass.h"
#include "RenderGraphUtils.h"

class FSailSimRenderDebug
{
public:
    static bool IsEnabled();
    static void AddGPUStretchDebug(
        FRDGBuilder& Graph,
        FRDGBufferSRVRef PositionSRV,
        FRDGBufferSRVRef StretchPairsSRV,
        uint32 NumPairs,
        const FViewInfo& View);

    static FRDGTextureRef GetOrCreateDebugTarget(FRDGBuilder& Graph, const FViewInfo& View);
};
