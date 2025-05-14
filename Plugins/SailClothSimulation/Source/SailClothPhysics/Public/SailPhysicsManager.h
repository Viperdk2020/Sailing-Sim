#pragma once
#include "CoreMinimal.h"
#include "RenderGraphResources.h"
class FSailPhysicsManager {
public:
    static FSailPhysicsManager& Get();
    void Init();
    void Release();
    void SolveStretch(FRDGBuilder& GraphBuilder, FRDGBufferRef Pos, FRDGBufferRef Constraints, uint32 Verts, uint32 Pairs, uint32 Iters);
};