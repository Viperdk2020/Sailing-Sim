
#pragma once
#include "CoreMinimal.h"
#include "RenderGraphResources.h"

// --- Persistent vertex buffers ---
struct FSailSimVertex
{
    FVector4f Position;   // xyz position, w = rest length or padding
};

struct FSailSimVelocity
{
    FVector4f Velocity;   // xyz vel, w padding
};

// --- Transient force buffer ---
struct FSailSimForce
{
    FVector4f Force;      // xyz force, w padding
};

// --- Constraint entries ---
struct FSailSimStretchPair
{
    uint32 Index0;
    uint32 Index1;
};

struct FSailSimBendTriplet
{
    uint32 Index0;
    uint32 Index1;
    uint32 Index2;
    uint32 Pad;
};

// --- Aerodynamic strip info ---
struct FSailSimStripInfo
{
    FVector3f Center;
    float     Area;
    FVector3f Normal;
    float     Pad;
};

// Convenience struct of RDG refs
struct FSailSimBuffers
{
    FRDGBufferRef Position = nullptr;
    FRDGBufferRef Velocity = nullptr;
    FRDGBufferRef Forces   = nullptr;
};
