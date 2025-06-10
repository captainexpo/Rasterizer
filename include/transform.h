#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "datatypes.h"

typedef struct {
  float pitch;
  float yaw;
  float roll;
  float3 position;
  float scale;
} ModelTransform;

float3 toWorldPoint(ModelTransform *transform, float3 point);
float3 rotatePoint(float3 point, float x, float y, float z);
float3 localToWorldDir(float3 local, ModelTransform *t);
#endif
