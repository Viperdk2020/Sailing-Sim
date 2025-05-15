#pragma once

#include "CoreMinimal.h"
#include "PrimitiveViewRelevance.h"
#include "PrimitiveSceneProxy.h"
#include "SailRenderDeformer.h"

class FSailPhysicsManager;

class FSailClothSceneProxy : public FPrimitiveSceneProxy
{
public:
    FSailClothSceneProxy(class USailClothComponent* InComponent, FSailPhysicsManager* InPhysicsManager);
    virtual ~FSailClothSceneProxy();

    virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily,
                                        uint32 VisibilityMap, FMeshElementCollector& Collector) const override;

    virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;

    virtual uint32 GetMemoryFootprint(void) const override { return sizeof(*this) + GetAllocatedSize(); }
    uint32 GetAllocatedSize(void) const { return FPrimitiveSceneProxy::GetAllocatedSize(); }

private:
    FSailRenderDeformer VertexFactory;
    FSailPhysicsManager* PhysicsManager;
    FMaterialRenderProxy* MaterialProxy;
    int32 VertexCount;
};
