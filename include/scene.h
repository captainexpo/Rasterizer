#ifndef SCENE_H
#define SCENE_H

#include "renderer.h"

void sceneStart(int argc, char **argv);
void sceneUpdate(float deltaTime);
void onRender(void);
extern RasterizerCamera mainCamera;

#endif
