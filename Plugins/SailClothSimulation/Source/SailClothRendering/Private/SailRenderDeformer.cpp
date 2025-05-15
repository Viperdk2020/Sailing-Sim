#include "SailRenderDeformer.h"
#include "ShaderParameterUtils.h"
#include "RHICommandList.h"

FSailRenderDeformer::FSailRenderDeformer(ERHIFeatureLevel::Type InFeatureLevel)
    : FVertexFactory(InFeatureLevel)
{
}

void FSailRenderDeformer::InitRHI()
{
    FVertexStreamComponent VertexStream(PositionSRV, 0, sizeof(FVector4f), VET_Float4);
    FVertexStreamComponent IndexStream(IndexBufferRHI, 0, sizeof(uint32), VET_UInt);

    FVertexDeclarationElementList Elements;
    Elements.Add(AccessStream(VertexStream, 0, "POSITION"));

    InitDeclaration(Elements);
}

void FSailRenderDeformer::BindBuffers(FRWBufferStructured& InPositions, FVertexBufferRHIRef& InIndexBuffer)
{
    PositionSRV = InPositions.SRV;
    IndexBufferRHI = InIndexBuffer;

    UpdateRHI();
}
