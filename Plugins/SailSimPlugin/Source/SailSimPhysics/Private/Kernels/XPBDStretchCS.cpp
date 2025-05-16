
#include "Kernels/XPBDStretchCS.h"
IMPLEMENT_GLOBAL_SHADER(FXPBDStretchCS, "/Shaders/XPBDStretch.usf", "MainCS", SF_Compute);
