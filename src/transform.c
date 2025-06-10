#include "../include/transform.h"
#include <math.h>

float3 rotatePoint(float3 point, float x, float y, float z) {
  float alpha = z; // yawn
  float beta = y;  // pitcher
  float gamma = x; // rollerblades

  float ca = cosf(alpha), sa = sinf(alpha);
  float cb = cosf(beta), sb = sinf(beta);
  float cg = cosf(gamma), sg = sinf(gamma);

  // Scary matrix multiplication
  float r00 = cb * cg;
  float r01 = sa * sb * cg - ca * sg;
  float r02 = ca * sb * cg + sa * sg;

  float r10 = cb * sg;
  float r11 = sa * sb * sg + ca * cg;
  float r12 = ca * sb * sg - sa * cg;

  float r20 = -sb;
  float r21 = sa * cb;
  float r22 = ca * cb;

  // Apply the matrix :)
  float x_rot = r00 * point.x + r01 * point.y + r02 * point.z;
  float y_rot = r10 * point.x + r11 * point.y + r12 * point.z;
  float z_rot = r20 * point.x + r21 * point.y + r22 * point.z;

  return (float3){x_rot, y_rot, z_rot};
}

float3 toWorldPoint(ModelTransform *transform, float3 point) {

  point = scalarmul3(point, transform->scale);
  point = rotatePoint(point, transform->roll, transform->pitch, transform->yaw);
  point = add3(point, transform->position);

  return point;
}

float3 localToWorldDir(float3 local, ModelTransform *transform) {
  float cy = cosf(transform->yaw), sy = sinf(transform->yaw);
  float cp = cosf(transform->pitch), sp = sinf(transform->pitch);
  float cr = cosf(transform->roll), sr = sinf(transform->roll);

  // Apply roll, then pitch, then yaw (Z → X → Y)
  float3 rolled = {cr * local.x - sr * local.y, sr * local.x + cr * local.y,
                   local.z};

  float3 pitched = {rolled.x, cp * rolled.y - sp * rolled.z,
                    sp * rolled.y + cp * rolled.z};

  float3 world = {cy * pitched.x + sy * pitched.z, pitched.y,
                  -sy * pitched.x + cy * pitched.z};

  return world;
}
