#pragma once

#include "CoreMinimal.h"
#include "RenderResource.h"
#include "VertexFactory.h"
#include "RHIResources.h"

class FSailRenderDeformer : public FVertexFactory
{
public:
    FSailRenderDeformer(ERHIFeatureLevel::Type InFeatureLevel);
    void InitRHI() override;

    void BindBuffers(FRWBufferStructured& InPositions, FVertexBufferRHIRef& InIndexBuffer);

private:
    FShaderResourceViewRHIRef PositionSRV;
    FVertexBufferRHIRef IndexBufferRHI;
};
