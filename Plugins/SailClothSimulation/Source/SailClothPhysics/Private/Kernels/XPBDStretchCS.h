#pragma once
#include "GlobalShader.h"
#include "ShaderParameterStruct.h"
class FXPBDStretchCS : public FGlobalShader {
    DECLARE_GLOBAL_SHADER(FXPBDStretchCS);
    SHADER_USE_PARAMETER_STRUCT(FXPBDStretchCS, FGlobalShader);
    BEGIN_SHADER_PARAMETER_STRUCT(FParameters,)
        SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<float4>, Positions)
        SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<uint2>, Constraints)
        SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<float4>, OutPositions)
        SHADER_PARAMETER(uint32, NumVerts)
        SHADER_PARAMETER(uint32, NumConstraints)
    END_SHADER_PARAMETER_STRUCT()
};