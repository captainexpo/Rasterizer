#ifndef SCENE_H
#define SCENE_H

#include "transform.h"

void sceneStart(int argc, char **argv);
void sceneUpdate(float deltaTime);

typedef struct {
  float FOV;
  float3 backgroundColor;
  ModelTransform transform;
} RasterizerCamera;

#endif
