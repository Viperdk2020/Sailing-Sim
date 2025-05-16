
#pragma once
#include "GlobalShader.h"
#include "ShaderParameterStruct.h"

class FXPBDBendCS : public FGlobalShader
{
    DECLARE_GLOBAL_SHADER(FXPBDBendCS);
    SHADER_USE_PARAMETER_STRUCT(FXPBDBendCS, FGlobalShader);

    BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
        SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<float4>, Positions)
        SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<uint4>,  BendData)
        SHADER_PARAMETER(float, DeltaTime)
        SHADER_PARAMETER(uint32, NumConstraints)
    END_SHADER_PARAMETER_STRUCT()
};
