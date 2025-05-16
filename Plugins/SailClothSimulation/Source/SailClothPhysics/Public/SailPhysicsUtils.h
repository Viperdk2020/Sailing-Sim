#pragma once

#include "CoreMinimal.h"
#include "RHI.h"
#include "RenderResource.h"
#include "RHIResources.h"

/**
 * Utility class containing physics-related helper functions for the SailClothPhysics module.
 */
class SAILCLOTHPHYSICS_API FSailPhysicsUtils
{
public:

    FORCEINLINE static void ApplyForce(FVector4f& Position, FVector4f& Velocity, const FVector4f& Force, float DeltaTime)
    {
        FVector4f Acceleration = Force;
        Velocity += Acceleration * DeltaTime;
        Position += Velocity * DeltaTime;
    }

    FORCEINLINE static void ClampVelocity(FVector4f& Velocity, float MaxVelocity)
    {
        float Speed = Velocity.Size();
        if (Speed > MaxVelocity)
        {
            Velocity *= (MaxVelocity / Speed);
        }
    }

    FORCEINLINE static void InitializeBuffer(FRWBufferStructured& Buffer, uint32 ElementSize, uint32 ElementCount, EBufferUsageFlags UsageFlags)
    {
       // Buffer.Initialize(ElementSize, ElementCount, UsageFlags);
    }

    FORCEINLINE static void ReleaseBuffer(FRWBufferStructured& Buffer)
    {
        Buffer.Release();
    }

    FORCEINLINE static void ZeroBuffer(FRWBufferStructured& Buffer)
    {
        if (Buffer.Buffer != nullptr)
        {
          //  void* Data = RHILockBuffer(Buffer.Buffer, 0, Buffer.NumBytes, RLM_WriteOnly);
          //  FMemory::Memzero(Data, Buffer.NumBytes);
         //   RHIUnlockBuffer(Buffer.Buffer);
        }
    }
};
