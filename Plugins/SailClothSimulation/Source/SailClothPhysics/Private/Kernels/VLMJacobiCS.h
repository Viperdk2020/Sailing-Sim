#pragma once
#include "GlobalShader.h"
#include "ShaderParameterStruct.h"

class FVLMJacobiCS : public FGlobalShader
{
    DECLARE_GLOBAL_SHADER(FVLMJacobiCS);
    SHADER_USE_PARAMETER_STRUCT(FVLMJacobiCS, FGlobalShader);

public:
    BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
        SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<float4>, CurrentVorticity)
        SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<float4>, VelocityField)
        SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<float4>, OutVorticity)
        SHADER_PARAMETER(float, RelaxationFactor)
        SHADER_PARAMETER(float, DeltaTime)
        SHADER_PARAMETER(uint32, VertexCount)
    END_SHADER_PARAMETER_STRUCT()
};
