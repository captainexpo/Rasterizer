#include "../include/triangle.h"
#include <math.h>
float signedArea(float2 check, float2 pa, float2 pb) {
  return (pb.x - pa.x) * (check.y - pa.y) - (pb.y - pa.y) * (check.x - pa.x);
}

bool pointInTriangle(float2 check, float2 pa, float2 pb, float2 pc,
                     float3 *weights) {

  float areaABP = signedArea(check, pa, pb);
  float areaBCP = signedArea(check, pb, pc);
  float areaCAP = signedArea(check, pc, pa);
  bool isInside = areaABP <= 0 && areaBCP <= 0 && areaCAP <= 0;

  bool hasNoArea = (areaABP + areaBCP + areaABP == 0);
  float inverseArea =
      !hasNoArea ? 1.0f / (areaABP + areaBCP + areaCAP) : 1.0f / 3.0f;

  weights->x = fabsf(areaBCP * inverseArea);
  weights->y = fabsf(areaCAP * inverseArea);
  weights->z = fabsf(areaABP * inverseArea);

  return isInside && !hasNoArea;
}
