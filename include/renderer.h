#ifndef RENDERER_H
#define RENDERER_H

#include "model.h"
#include "scene.h"
#include "window.h"
float3 worldPointToScreen(RasterizerCamera *camera, float3 point);
void drawModel(RasterizerModel *model, Frame *frame, RasterizerCamera *camera);
void initFrame(void);
Frame *getFrame(RasterizerCamera *camera, RasterizerModel **models);
extern RasterizerModel **RASTERIZER_MODEL_QUEUE;
extern RasterizerCamera *RASTERIZER_MAIN_CAMERA;
#endif
