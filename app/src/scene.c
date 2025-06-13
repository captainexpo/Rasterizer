#include "scene.h"
#include "../include/objloader.h"
#include "datatypes.h"
#include "model.h"
#include "renderer.h"
#include "transform.h"
#include <math.h>
#include <raylib.h>
#include <stdio.h>

RasterizerModel **models;
RasterizerCamera mainCamera = {
    .FOV = 60.0f,
    .backgroundColor = {100, 100, 150},
    .transform =
        {
            .pitch = 0,
            .yaw = 0,
            .roll = 0,
            .position = {0, 0, 0},
            .scale = 1.0f,
        },
};

float totalTime = 0.0f;

void sceneUpdate(float deltaTime) {
  const float ROT_SPEED = 0.8f;
  const float MOVE_SPEED = 10.0f;
  if (IsKeyDown(KEY_LEFT))
    mainCamera.transform.yaw -= ROT_SPEED * deltaTime;
  if (IsKeyDown(KEY_RIGHT))
    mainCamera.transform.yaw += ROT_SPEED * deltaTime;
  if (IsKeyDown(KEY_UP))
    mainCamera.transform.pitch += ROT_SPEED * deltaTime;
  if (IsKeyDown(KEY_DOWN))
    mainCamera.transform.pitch -= ROT_SPEED * deltaTime;
  if (IsKeyDown(KEY_W))
    mainCamera.transform.position =
        add3(mainCamera.transform.position,
             localToWorldDir((float3){0, 0, MOVE_SPEED * deltaTime},
                             &mainCamera.transform));
  if (IsKeyDown(KEY_S))
    mainCamera.transform.position =
        add3(mainCamera.transform.position,
             localToWorldDir((float3){0, 0, -MOVE_SPEED * deltaTime},
                             &mainCamera.transform));
  if (IsKeyDown(KEY_A))
    mainCamera.transform.position =
        add3(mainCamera.transform.position,
             localToWorldDir((float3){-MOVE_SPEED * deltaTime, 0, 0},
                             &mainCamera.transform));
  if (IsKeyDown(KEY_D))
    mainCamera.transform.position =
        add3(mainCamera.transform.position,
             localToWorldDir((float3){MOVE_SPEED * deltaTime, 0, 0},
                             &mainCamera.transform));

  totalTime += deltaTime;
}

void sceneStart(int argc, char **argv) {
  (void)argc;
  (void)argv;
  models = malloc(sizeof(RasterizerModel *) * 3);
  models[0] = loadOBJFile("../../models/player.obj");
  models[0]->transform = (ModelTransform){
      .pitch = 0,
      .yaw = 0,
      .roll = M_PI,
      .position = {0, 0, 25},
      .scale = 0.1f,
  };
  models[0]->texture =
      readPNGImage("../../models/textures/quake_character.png");
  models[1] = loadOBJFile("../../models/shambler.obj");
  models[1]->transform = (ModelTransform){
      .pitch = M_PI,
      .yaw = 0,
      .roll = M_PI,
      .position = {0, 0, 10},
      .scale = 0.05f,
  };
  models[1]->texture = readPNGImage("../../models/textures/shambler.png");
  models[2] = NULL;
}

void onRender(void) {
  for (RasterizerModel **m = models; *m != NULL; m++) {
    addModelToQueue(*m);
  }
}
