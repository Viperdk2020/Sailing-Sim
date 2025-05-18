
#include "Kernels/IntegrateHalfDTCS.h"
IMPLEMENT_GLOBAL_SHADER(FIntegrateHalfDTCS, "/SailSimPlugin/IntegrateHalfDT.usf", "MainCS", SF_Compute);
