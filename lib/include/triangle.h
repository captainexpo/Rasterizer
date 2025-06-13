#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "datatypes.h"
#include <stdbool.h>

bool pointInTriangle(float2 check, float2 pa, float2 pb, float2 pc,
                     float3 *weights);

#endif
