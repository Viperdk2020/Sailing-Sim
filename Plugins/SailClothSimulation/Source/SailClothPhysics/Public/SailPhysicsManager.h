#pragma once

#include "CoreMinimal.h"
#include "RHI.h"
#include "RHICommandList.h"
#include "RenderGraphResources.h"
#include "RenderGraphBuilder.h"
//#include "MinimalRDGBuffer.h"





struct FPersistentRDGSimBuffer
{
    TRefCountPtr<FRDGPooledBuffer> Buffer;
    uint32 NumElements = 0;
    uint32 Stride = 0;

    void Initialize(FRHICommandListBase& RHICmdList, uint32 InNumElements, uint32 InStride, const TCHAR* DebugName)
    {
        Release();

        NumElements = InNumElements;
        Stride = InStride;

        FRDGBufferDesc Desc = FRDGBufferDesc::CreateStructuredDesc(InStride, InNumElements);
        Buffer = FRDGBufferPool.FindFreeBuffer(RHICmdList, Desc, DebugName, ERDGPooledBufferAlignment::Default);
    }

    void Release()
    {
        Buffer.SafeRelease();
        NumElements = 0;
        Stride = 0;
    }

    FRHIBuffer* GetRHI() const
    {
        return Buffer.IsValid() ? Buffer->GetRHI() : nullptr;
    }
};





class FSailPhysicsManager
{
public:
    FSailPhysicsManager();
    ~FSailPhysicsManager();

    void Initialize(uint32 InVertexCount);
    void Release();
    void Simulate(FRHICommandListImmediate& RHICmdList, float DeltaTime);

    FPersistentRDGSimBuffer& GetPositionsBuffer() { return PositionsBuffer; }
    FPersistentRDGSimBuffer& GetVelocitiesBuffer() { return VelocitiesBuffer; }
    FPersistentRDGSimBuffer& GetNormalsBuffer() { return NormalsBuffer; }

private:
    uint32 VertexCount = 0;
    uint32 GroupSize = 64;

    FPersistentRDGSimBuffer PositionsBuffer;
    FPersistentRDGSimBuffer VelocitiesBuffer;
    FPersistentRDGSimBuffer NormalsBuffer;

    void DispatchXPBDStretchCS(FRDGBuilder& GraphBuilder, float DeltaTime);
    void DispatchXPBDBendCS(FRDGBuilder& GraphBuilder, float DeltaTime);
    void DispatchVLMJacobiCS(FRDGBuilder& GraphBuilder, float DeltaTime);
};