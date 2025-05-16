#pragma once

#include "CoreMinimal.h"
#include "RenderResource.h"
#include "VertexFactory.h"
#include "RHIResources.h"

class FSailRenderDeformer : public FVertexFactory
{
public:
    FSailRenderDeformer(ERHIFeatureLevel::Type InFeatureLevel);
    

   

private:
    FShaderResourceViewRHIRef PositionSRV;
    FVertexBuffer IndexBufferRHI;
};
