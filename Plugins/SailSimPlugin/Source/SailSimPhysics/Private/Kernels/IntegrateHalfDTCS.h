
#pragma once
#include "GlobalShader.h"
#include "ShaderParameterStruct.h"
class FIntegrateHalfDTCS : public FGlobalShader
{
    DECLARE_GLOBAL_SHADER(FIntegrateHalfDTCS);
    SHADER_USE_PARAMETER_STRUCT(FIntegrateHalfDTCS, FGlobalShader);
    BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
        SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<float4>, Positions)
        SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<float4>, Velocity)
        SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<int>, Forces)
        SHADER_PARAMETER(float, DeltaTime)
        SHADER_PARAMETER(uint32, NumVerts)
    END_SHADER_PARAMETER_STRUCT()
};
