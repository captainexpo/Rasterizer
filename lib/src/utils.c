#include "../include/utils.h"
#include <stdlib.h>

inline float randRange(float min, float max) {
  return min + (rand() / (float)RAND_MAX * (max - min));
}
inline float min(float a, float b) { return a < b ? a : b; }
inline float max(float a, float b) { return a > b ? a : b; }
