#include "SailClothSimShaders.h"
#include "RHICommandList.h"
#include "ShaderParameterUtils.h"
#include "RenderGraphUtils.h"
#include "Misc/ScopeLock.h"

#define THREAD_GROUP_SIZE 64

// Shader Implementation Macros
IMPLEMENT_GLOBAL_SHADER(FSailClothCS, "/Plugin/SailClothSimulation/Shaders/Cloth/SailClothSim.usf", "MainCS", SF_Compute);
IMPLEMENT_GLOBAL_SHADER(FStretchConstraintCS, "/Plugin/SailClothSimulation/Shaders/Constraints/ApplyStretchConstraints.usf", "MainCS", SF_Compute);
IMPLEMENT_GLOBAL_SHADER(FBendConstraintCS, "/Plugin/SailClothSimulation/Shaders/Constraints/ApplyBendConstraints.usf", "MainCS", SF_Compute);
IMPLEMENT_GLOBAL_SHADER(FVLMJacobiCS, "/Plugin/SailClothSimulation/Shaders/VLM/VLMJacobiSolver.usf", "MainCS", SF_Compute);

// Utility function for buffer creation
template<typename T>
static void CreateStructuredBuffer(
    FRHICommandListImmediate& RHICmdList,
    FRWBufferStructured& Buffer,
    const TArray<T>& Data,
    const TCHAR* DebugName)
{
    Buffer.Initialize(
        sizeof(T),
        Data.Num(),
        PF_R32_FLOAT,
        BUF_UnorderedAccess | BUF_ShaderResource,
        DebugName
    );

    void* Ptr = RHILockStructuredBuffer(Buffer.Buffer, 0, Data.Num() * sizeof(T), RLM_WriteOnly);
    FMemory::Memcpy(Ptr, Data.GetData(), Data.Num() * sizeof(T));
    RHIUnlockStructuredBuffer(Buffer.Buffer);
}

// Initialization function for SailClothSimContext
void FSailClothSimShaders::Initialize(
    FRHICommandListImmediate& RHICmdList,
    FSailClothSimContext& Ctx,
    int32 GridWidth,
    int32 GridHeight)
{
    Ctx.NumParticles = GridWidth * GridHeight;
    Ctx.NumStrips = GridWidth;
    Ctx.NumStretchConstraints = (GridWidth - 1) * GridHeight + (GridHeight - 1) * GridWidth;
    Ctx.NumBendConstraints = (GridWidth - 1) * (GridHeight - 1) * 2;

    // Initialize Buffers
    TArray<FParticleGPU> Particles;
    Particles.SetNum(Ctx.NumParticles);

    for (int32 y = 0; y < GridHeight; ++y)
    {
        for (int32 x = 0; x < GridWidth; ++x)
        {
            int32 Index = y * GridWidth + x;
            Particles[Index].Position = FVector3f(x * 10.f, y * 10.f, 0.f);
            Particles[Index].PrevPosition = Particles[Index].Position;
            Particles[Index].Mass = 1.0f;
            Particles[Index].Area = 10.0f;
            Particles[Index].Normal = FVector3f(0, 0, 1);
        }
    }

    CreateStructuredBuffer(RHICmdList, Ctx.ParticleBuffer, Particles, TEXT("ParticleBuffer"));

    // Stretch Constraints
    TArray<FIntPoint> StretchConstraints;
    TArray<float> StretchRestLengths;
    for (int32 y = 0; y < GridHeight; ++y)
    {
        for (int32 x = 0; x < GridWidth; ++x)
        {
            int32 Index = y * GridWidth + x;
            if (x < GridWidth - 1)
            {
                StretchConstraints.Add(FIntPoint(Index, Index + 1));
                StretchRestLengths.Add(10.0f);
            }
            if (y < GridHeight - 1)
            {
                StretchConstraints.Add(FIntPoint(Index, Index + GridWidth));
                StretchRestLengths.Add(10.0f);
            }
        }
    }

    CreateStructuredBuffer(RHICmdList, Ctx.StretchConstraintBuffer, StretchConstraints, TEXT("StretchConstraints"));
    CreateStructuredBuffer(RHICmdList, Ctx.StretchRestLengthBuffer, StretchRestLengths, TEXT("StretchRestLengths"));
}

// Unified Simulation Dispatch
void FSailClothSimShaders::Simulate(
    FRHICommandListImmediate& RHICmdList,
    FSailClothSimContext& Ctx,
    float DeltaTime,
    FVector3f Wind,
    float AirDensity,
    float Compliance,
    float StretchStiffness,
    float BendStiffness)
{
    FIntVector ThreadGroupSize(THREAD_GROUP_SIZE, 1, 1);

    // Sail Cloth Simulation
    {
        TShaderMapRef<FSailClothCS> Shader(GetGlobalShaderMap(GMaxRHIFeatureLevel));

        FSailClothCS::FParameters Params;
        Params.DeltaTime = DeltaTime;
        Params.Wind = Wind;
        Params.AirDensity = AirDensity;
        Params.Particles = Ctx.ParticleBuffer.SRV;
        Params.RWParticles = Ctx.ParticleBuffer.UAV;

        FComputeShaderUtils::Dispatch(
            RHICmdList,
            Shader,
            Params,
            FIntVector(FMath::DivideAndRoundUp(Ctx.NumParticles, THREAD_GROUP_SIZE), 1, 1)
        );
    }

    // Stretch Constraints
    {
        TShaderMapRef<FStretchConstraintCS> Shader(GetGlobalShaderMap(GMaxRHIFeatureLevel));

        FStretchConstraintCS::FParameters Params;
        Params.DeltaTime = DeltaTime;
        Params.Compliance = Compliance;
        Params.StretchStiffness = StretchStiffness;
        Params.Particles = Ctx.ParticleBuffer.SRV;
        Params.RWParticles = Ctx.ParticleBuffer.UAV;
        Params.StretchConstraints = Ctx.StretchConstraintBuffer.SRV;
        Params.StretchRestLengths = Ctx.StretchRestLengthBuffer.SRV;

        FComputeShaderUtils::Dispatch(
            RHICmdList,
            Shader,
            Params,
            FIntVector(FMath::DivideAndRoundUp(Ctx.NumStretchConstraints, THREAD_GROUP_SIZE), 1, 1)
        );
    }
}

// Cleanup Function
void FSailClothSimShaders::Release(FSailClothSimContext& Ctx)
{
    Ctx.ParticleBuffer.Release();
    Ctx.StretchConstraintBuffer.Release();
    Ctx.StretchRestLengthBuffer.Release();
}
