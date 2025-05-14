#pragma once
#include "CoreMinimal.h"
#include "RenderGraphResources.h"
class FSailRenderDeformer {
public:
    static void QueueMeshUpdate(FRDGBuilder& GraphBuilder, FRDGBufferRef SimulatedPos, const FTransform& LocalToWorld);
};