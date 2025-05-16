#pragma once
#include "GlobalShader.h"
#include "ShaderParameterStruct.h"

class FXPBDBendCS : public FGlobalShader
{
    DECLARE_GLOBAL_SHADER(FXPBDBendCS);
    SHADER_USE_PARAMETER_STRUCT(FXPBDBendCS, FGlobalShader);

public:
    BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
        SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<float4>, Positions)
        SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<float4>, Velocities)
        SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<float4>, OutPositions)
        SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<float4>, OutVelocities)
        SHADER_PARAMETER(float, BendStiffness)
        SHADER_PARAMETER(float, DeltaTime)
        SHADER_PARAMETER(uint32, VertexCount)
    END_SHADER_PARAMETER_STRUCT()
};
