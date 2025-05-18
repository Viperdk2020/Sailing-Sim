

#pragma once

#include "CoreMinimal.h"
#include "Kernels/VLMJacobiCS.h"
#include "Kernels/XPBDBendCS.h"
#include "Kernels/XPBDStretchCS.h"
#include "Kernels/IntegrateHalfDTCS.h"

#include "RenderGraphUtils.h"    // for FComputeShaderUtils::AddPass, GraphBuilder.AddPass, etc.
#include "RenderGraphBuilder.h"
#include "SailSimPhysicsUtils.h"

/**
 * 
 */
class SAILSIMPHYSICS_API SailSimSailPhyiscsManager
{
public:
	SailSimSailPhyiscsManager();
	~SailSimSailPhyiscsManager();
};
