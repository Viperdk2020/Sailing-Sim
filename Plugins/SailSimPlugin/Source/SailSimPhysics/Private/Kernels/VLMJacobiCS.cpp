
#include "Kernels/VLMJacobiCS.h"
IMPLEMENT_GLOBAL_SHADER(FVLMJacobiCS, "/SailSimPlugin/VLMJacobi.usf", "MainCS", SF_Compute);
