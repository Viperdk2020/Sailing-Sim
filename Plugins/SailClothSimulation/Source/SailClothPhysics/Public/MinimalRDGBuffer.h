#pragma once

#include "CoreMinimal.h"
#include "RHI.h"
#include "RenderGraphResources.h"

struct FMinimalRDGBuffer
{
    TRefCountPtr<FRDGPooledBuffer> Buffer;
    uint32 NumElements = 0;
    uint32 Stride = 0;

    void Initialize(uint32 InNumElements, uint32 InStride, const TCHAR* DebugName)
    {
        Release();
        NumElements = InNumElements;
        Stride = InStride;
       // Buffer = FRDGPooledBuffer::Create(FRDGBufferDesc::CreateStructuredDesc(InStride, InNumElements), DebugName);
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