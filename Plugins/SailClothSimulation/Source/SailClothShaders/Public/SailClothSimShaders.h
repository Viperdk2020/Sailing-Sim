#pragma once

#include "CoreMinimal.h"
#include "RenderCore.h"
#include "RHIResources.h"
#include "GlobalShader.h"
#include "ShaderParameterStruct.h"
#include "RenderGraphUtils.h"
#include "RendererInterface.h"
#include "ShaderParameterUtils.h"
#include "DynamicRHI.h"
#include "RHIUtilities.h"
#include "RenderResource.h"
#include "Math/UnrealMathUtility.h"

#define THREAD_GROUP_SIZE 64

// ====================================================================================
// Particle GPU Data Structure (Shared with HLSL)
// ====================================================================================

struct FParticleGPU
{
    FVector3f Position;
    FVector3f PrevPosition;
    FVector3f Velocity;
    FVector3f Normal;  // Surface normal for aerodynamic calculations
    float Area;        // Effective area for lift/drag calculations
    float Mass;
};

// ====================================================================================
// Sail Cloth Simulation Context
// ====================================================================================

struct SAILCLOTHSHADERS_API FSailClothSimContext
{
    FRWBufferStructured ParticleBuffer;
    FRWBufferStructured StretchConstraintBuffer;
    FRWBufferStructured StretchRestLengthBuffer;
    FRWBufferStructured BendConstraintBuffer;
    FRWBufferStructured BendRestAngleBuffer;
    FRWBufferStructured InfluenceMatrixBuffer;
    FRWBufferStructured RHSBuffer;
    FRWBufferStructured GammaBufferRead;
    FRWBufferStructured GammaBufferWrite;
    FRWBufferStructured ResidualsBuffer;  // Residuals for VLM convergence tracking

    int32 NumParticles = 0;
    int32 NumStretchConstraints = 0;
    int32 NumBendConstraints = 0;
    int32 NumStrips = 0;
    int32 VLMNumIterations = 16;
};

// ====================================================================================
// Sail Cloth Simulation Shaders Interface
// ====================================================================================

struct SAILCLOTHSHADERS_API FSailClothSimShaders
{
    /**
     * Initialize and upload all buffers
     */
    static void Initialize(
        FRHICommandListImmediate& RHICmd,
        FSailClothSimContext& Ctx,
        int32 GridWidth,
        int32 GridHeight
    );

    /**
     * Release all buffers
     */
    static void Release(FSailClothSimContext& Ctx);

    /**
     * One-line call from Game Thread
     */
    static void Simulate(
        FRHICommandListImmediate& RHICmd,
        FSailClothSimContext& Ctx,
        float DeltaTime,
        FVector3f Wind = FVector3f(500.0f, 0.0f, 0.0f),
        float AirDensity = 1.225f,
        float Compliance = 0.001f,
        float StretchStiffness = 0.9f,
        float BendStiffness = 0.7f
    );
};

// ====================================================================================
// Cloth Integration + Wind/Drag Shader
// ====================================================================================

class FSailClothCS : public FGlobalShader
{
    DECLARE_GLOBAL_SHADER(FSailClothCS);
    SHADER_USE_PARAMETER_STRUCT(FSailClothCS, FGlobalShader);

    BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
        SHADER_PARAMETER(float, DeltaTime)
        SHADER_PARAMETER(FVector3f, Wind)
        SHADER_PARAMETER(float, AirDensity)
        SHADER_PARAMETER_SRV(StructuredBuffer<FParticleGPU>, Particles)
        SHADER_PARAMETER_UAV(RWStructuredBuffer<FParticleGPU>, RWParticles)
    END_SHADER_PARAMETER_STRUCT()

    static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
    {
        return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM6);
    }
};

// ====================================================================================
// Stretch Constraint Shader
// ====================================================================================

class FStretchConstraintCS : public FGlobalShader
{
    DECLARE_GLOBAL_SHADER(FStretchConstraintCS);
    SHADER_USE_PARAMETER_STRUCT(FStretchConstraintCS, FGlobalShader);

    BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
        SHADER_PARAMETER(float, DeltaTime)
        SHADER_PARAMETER(float, Compliance)
        SHADER_PARAMETER(float, StretchStiffness)
        SHADER_PARAMETER_SRV(StructuredBuffer<FParticleGPU>, Particles)
        SHADER_PARAMETER_UAV(RWStructuredBuffer<FParticleGPU>, RWParticles)
        SHADER_PARAMETER_SRV(StructuredBuffer<FIntPoint>, StretchConstraints)
        SHADER_PARAMETER_SRV(StructuredBuffer<float>, StretchRestLengths)
    END_SHADER_PARAMETER_STRUCT()

    static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
    {
        return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM6);
    }
};

// ====================================================================================
// Bend Constraint Shader
// ====================================================================================

class FBendConstraintCS : public FGlobalShader
{
    DECLARE_GLOBAL_SHADER(FBendConstraintCS);
    SHADER_USE_PARAMETER_STRUCT(FBendConstraintCS, FGlobalShader);

    BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
        SHADER_PARAMETER(float, DeltaTime)
        SHADER_PARAMETER(float, Compliance)
        SHADER_PARAMETER(float, BendStiffness)
        SHADER_PARAMETER_SRV(StructuredBuffer<FParticleGPU>, Particles)
        SHADER_PARAMETER_UAV(RWStructuredBuffer<FParticleGPU>, RWParticles)
        SHADER_PARAMETER_SRV(StructuredBuffer<FIntPoint>, BendConstraints)
        SHADER_PARAMETER_SRV(StructuredBuffer<float>, BendRestAngles)
    END_SHADER_PARAMETER_STRUCT()

    static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
    {
        return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM6);
    }
};

// ====================================================================================
// VLM Jacobi Solver Shader
// ====================================================================================

class FVLMJacobiCS : public FGlobalShader
{
    DECLARE_GLOBAL_SHADER(FVLMJacobiCS);
    SHADER_USE_PARAMETER_STRUCT(FVLMJacobiCS, FGlobalShader);

    BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
        SHADER_PARAMETER(uint32, N)
        SHADER_PARAMETER(uint32, NumIterations)
        SHADER_PARAMETER(float, Tolerance)
        SHADER_PARAMETER_SRV(StructuredBuffer<float>, InfluenceMatrix)
        SHADER_PARAMETER_SRV(StructuredBuffer<float>, RHS)
        SHADER_PARAMETER_SRV(StructuredBuffer<float>, GammaRead)
        SHADER_PARAMETER_UAV(RWStructuredBuffer<float>, GammaWrite)
        SHADER_PARAMETER_UAV(RWStructuredBuffer<float>, Residuals)
    END_SHADER_PARAMETER_STRUCT()

    static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
    {
        return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM6);
    }
};
