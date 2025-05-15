#pragma once

#include "CoreMinimal.h"
#include "RHI.h"
#include "RenderResource.h"
#include "RHIResources.h"

class FSailPhysicsManager
{
public:
    FSailPhysicsManager();
    ~FSailPhysicsManager();

    void Initialize(uint32 InVertexCount);
    void Release();

    /** Called every frame on game thread */
    void Tick(float DeltaTime);

private:
    void Simulate(FRHICommandListImmediate& RHICmdList, float DeltaTime);

    uint32 VertexCount = 0;
    FRWBufferStructured PositionsBuffer;
    FRWBufferStructured VelocitiesBuffer;
    FRWBufferStructured NormalsBuffer;

    void DispatchXPBDStretchCS(FRHICommandListImmediate& RHICmdList, float DeltaTime);
    void DispatchXPBDBendCS(FRHICommandListImmediate& RHICmdList, float DeltaTime);
    void DispatchVLMJacobiCS(FRHICommandListImmediate& RHICmdList, float DeltaTime);
};