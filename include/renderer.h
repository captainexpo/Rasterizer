#ifndef RENDERER_H
#define RENDERER_H

#include "model.h"
#include "scene.h"
#include "window.h"
float3 worldPointToScreen(RasterizerCamera *camera, float3 point);
void drawModel(RasterizerModel *model, Frame *frame, RasterizerCamera *camera);
void initFrame(void);
#endif
