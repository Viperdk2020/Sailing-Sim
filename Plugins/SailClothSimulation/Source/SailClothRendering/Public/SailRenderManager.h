#pragma once

#include "CoreMinimal.h"

class FSailPhysicsManager;
class FPrimitiveSceneProxy;
class USailClothComponent;

/**
 * Manages rendering for sail cloth.
 */
class SAILCLOTHRENDERING_API FSailRenderManager
{
public:
    FSailRenderManager();
    ~FSailRenderManager();

    void Initialize(FSailPhysicsManager* InPhysics, USailClothComponent* InComponent);
    void Release();

    /** Called every frame on game thread */
    void Tick();

private:
    FPrimitiveSceneProxy* SceneProxy = nullptr;
    USailClothComponent* Component = nullptr;
};