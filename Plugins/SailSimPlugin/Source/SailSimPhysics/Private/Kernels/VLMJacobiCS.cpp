
#include "Kernels/VLMJacobiCS.h"
IMPLEMENT_GLOBAL_SHADER(FVLMJacobiCS, "/Shaders/VLMJacobi.usf", "MainCS", SF_Compute);
