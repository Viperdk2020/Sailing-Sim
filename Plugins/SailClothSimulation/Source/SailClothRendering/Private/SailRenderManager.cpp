#include "SailRenderManager.h"
#include "SailClothSceneProxy.h"
#include "Engine/Engine.h"
#include "RendererInterface.h"
#include "RHICommandList.h"

FSailRenderManager::FSailRenderManager()
    : SceneProxy(nullptr), Component(nullptr)
{}

FSailRenderManager::~FSailRenderManager()
{
    Release();
}

void FSailRenderManager::Initialize(FSailPhysicsManager* InPhysics, USailClothComponent* InComponent)
{
    Component = InComponent;
    SceneProxy = new FSailClothSceneProxy(InComponent, InPhysics);
    if (SceneProxy)
    {
        SceneProxy->InitPrimitiveResource();
    }
}

void FSailRenderManager::Release()
{
    if (SceneProxy)
    {
        SceneProxy->ReleasePrimitiveResource();
        delete SceneProxy;
        SceneProxy = nullptr;
    }
    Component = nullptr;
}

void FSailRenderManager::Tick()
{
    ENQUEUE_RENDER_COMMAND(RenderCloth)(
        [This = this](FRHICommandListImmediate& RHICmdList)
        {
            if (!This->SceneProxy)
                return;

            TArray<const FSceneView*> Views;
            FSceneViewFamily ViewFamily(
                FSceneViewFamily::ConstructionValues(
                    GEngine->GameViewport->Viewport,
                    GEngine->GameViewport->GetWorld()->Scene,
                    GEngine->GameViewport->EngineShowFlags
                )
            );
            uint32 VisibilityMap = ~0u;

            This->SceneProxy->GetDynamicMeshElements(Views, ViewFamily, VisibilityMap, *new FMeshElementCollector());
        }
    );
}