#include "SailClothSceneProxy.h"
#include "SailRenderDeformer.h"
#include "SailPhysicsManager.h"
#include "SailPhysicsUtils.h"
#include "Materials/MaterialInterface.h"
#include "PrimitiveViewRelevance.h"
#include "SceneManagement.h"

FSailClothSceneProxy::FSailClothSceneProxy(USailClothComponent* InComponent, FSailPhysicsManager* InPhysicsManager)
    : FPrimitiveSceneProxy(InComponent),
      PhysicsManager(InPhysicsManager),
      VertexFactory(GetScene().GetFeatureLevel()),
      MaterialProxy(nullptr)
{
    check(PhysicsManager);

    VertexCount = PhysicsManager->GetPositionsBuffer().NumElements;

    // Bind physics position buffer to vertex factory
    ENQUEUE_RENDER_COMMAND(BindPositionBuffer)(
        [this, PhysicsManager](FRHICommandListImmediate& RHICmdList)
        {
            VertexFactory.BindPositionBuffer(RHICmdList, PhysicsManager->GetPositionsBuffer());
        });

    // Get material proxy from component material
    UMaterialInterface* Material = InComponent->GetMaterial(0);
    if (Material)
    {
        MaterialProxy = Material->GetRenderProxy();
    }
    else
    {
        MaterialProxy = UMaterial::GetDefaultMaterial(MD_Surface)->GetRenderProxy();
    }

    VertexFactory.InitResource();
}

FSailClothSceneProxy::~FSailClothSceneProxy()
{
    VertexFactory.ReleaseResource();
}

void FSailClothSceneProxy::GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily,
                                                  uint32 VisibilityMap, FMeshElementCollector& Collector) const
{
    for (int32 ViewIndex = 0; ViewIndex < Views.Num(); ViewIndex++)
    {
        if (!(VisibilityMap & (1 << ViewIndex)))
        {
            continue;
        }

        FDynamicMeshBuilder MeshBuilder(VertexFactory.GetFeatureLevel());

        // Here you should provide vertex/index data (or procedural geometry)
        // Since vertices come from GPU buffer, use a procedural draw call with vertex count

        // Example: build a simple triangle list from vertex count (this depends on your mesh topology)
        // For demo, assume VertexCount and topology are known and valid

        // TODO: Replace with actual index buffer or procedural setup if you have one
        // MeshBuilder.AddVertex(...);
        // MeshBuilder.AddTriangle(...);

        FMeshBatch& MeshBatch = Collector.AllocateMesh();
        MeshBatch.VertexFactory = &VertexFactory;
        MeshBatch.MaterialRenderProxy = MaterialProxy;
        MeshBatch.ReverseCulling = IsLocalToWorldDeterminantNegative();
        MeshBatch.Type = PT_TriangleList;
        MeshBatch.DepthPriorityGroup = SDPG_World;
        MeshBatch.bCanApplyViewModeOverrides = false;

        Collector.AddMesh(ViewIndex, MeshBatch);
    }
}

FPrimitiveViewRelevance FSailClothSceneProxy::GetViewRelevance(const FSceneView* View) const
{
    FPrimitiveViewRelevance Result;
    Result.bDrawRelevance = IsShown(View);
    Result.bDynamicRelevance = true;
    Result.bShadowRelevance = IsShadowCast(View);
    Result.bRenderCustomDepth = ShouldRenderCustomDepth();
    Result.bUsesLightingChannels = GetLightingChannelMask() != GetDefaultLightingChannelMask();
    Result.bOpaque = true;
    Result.bSeparateTranslucency = false;
    return Result;
}
