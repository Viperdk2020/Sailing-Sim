
#include "Kernels/IntegrateHalfDTCS.h"
IMPLEMENT_GLOBAL_SHADER(FIntegrateHalfDTCS, "/Shaders/IntegrateHalfDT.usf", "MainCS", SF_Compute);
