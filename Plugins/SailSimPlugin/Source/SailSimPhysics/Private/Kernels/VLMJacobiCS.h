
#pragma once
#include "GlobalShader.h"
#include "ShaderParameterStruct.h"
class FVLMJacobiCS : public FGlobalShader
{
    DECLARE_GLOBAL_SHADER(FVLMJacobiCS);
    SHADER_USE_PARAMETER_STRUCT(FVLMJacobiCS, FGlobalShader);
    BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
        SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<float4>, Positions)
        SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<float4>, StripInfo0)
        SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<uint2>,  StripInfo1)
        SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<int>,  Forces)
        SHADER_PARAMETER(uint32, NumConstraints)
    END_SHADER_PARAMETER_STRUCT()
};
