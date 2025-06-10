#include "../include/datatypes.h"
#include "../include/utils.h"

inline float2 newf2(float x, float y) { return (float2){x, y}; }
inline float3 newf3(float x, float y, float z) { return (float3){x, y, z}; }
inline float dot3(float3 a, float3 b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}
inline float dot2(float2 a, float2 b) { return a.x * b.x + a.y * b.y; }
inline float2 add2(float2 a, float2 b) {
  return (float2){a.x + b.x, a.y + b.y};
}
inline float2 sub2(float2 a, float2 b) {
  return (float2){a.x - b.x, a.y - b.y};
}
inline float3 add3(float3 a, float3 b) {
  return (float3){a.x + b.x, a.y + b.y, a.z + b.z};
}
inline float3 sub3(float3 a, float3 b) {
  return (float3){a.x - b.x, a.y - b.y, a.z - b.z};
}
inline float2 random2(float min, float max) {
  return (float2){randRange(min, max), randRange(min, max)};
}
inline float3 random3(float min, float max) {
  return (float3){randRange(min, max), randRange(min, max),
                  randRange(min, max)};
}
inline float3 scalarmul3(float3 a, float scalar) {
  return (float3){a.x * scalar, a.y * scalar, a.z * scalar};
}
inline float2 scalarmul2(float2 a, float scalar) {
  return (float2){a.x * scalar, a.y * scalar};
}
inline float2 truncate32(float3 a) {
  return (float2){a.x, a.y}; // Truncate to 2D
}
