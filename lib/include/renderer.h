#ifndef RENDERER_H
#define RENDERER_H

#include "model.h"
typedef struct {
  float FOV;
  float3 backgroundColor;
  ModelTransform transform;
} RasterizerCamera;

float3 worldPointToScreen(RasterizerCamera *camera, float3 point);
void addModelToQueue(RasterizerModel *model);
void initFrame(RasterizerCamera *camera);
// Frame *getFrame(RasterizerCamera *camera, RasterizerModel **models);
void renderFrame(RasterizerCamera *camera, int winWidth, int winHeight);
#endif
