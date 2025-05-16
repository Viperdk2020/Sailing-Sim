#pragma once

#include "CoreMinimal.h"

//class FSailPhysicsManager;
//class FPrimitiveSceneProxy;
//class USailClothComponent;

/**
 * Manages rendering for sail cloth.
 */
class FSailRenderManager
{
public:
    FSailRenderManager();
    ~FSailRenderManager();

    void Initialize();
    void Release();

    /** Called every frame on game thread */
    void Tick();

private:
    FPrimitiveSceneProxy* SceneProxy = nullptr;
   
};