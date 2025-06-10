#include "../include/scene.h"
#include "../include/datatypes.h"
#include "../include/model.h"
#include "../include/objloader.h"
#include "../include/renderer.h"
#include "../include/transform.h"
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_MODELS 1

RasterizerModel *models[NUM_MODELS] = {0};
RasterizerCamera camera = {
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
    camera.transform.yaw -= ROT_SPEED * deltaTime;
  if (IsKeyDown(KEY_RIGHT))
    camera.transform.yaw += ROT_SPEED * deltaTime;
  if (IsKeyDown(KEY_UP))
    camera.transform.pitch += ROT_SPEED * deltaTime;
  if (IsKeyDown(KEY_DOWN))
    camera.transform.pitch -= ROT_SPEED * deltaTime;
  if (IsKeyDown(KEY_W))
    camera.transform.position =
        add3(camera.transform.position,
             localToWorldDir((float3){0, 0, MOVE_SPEED * deltaTime},
                             &camera.transform));
  if (IsKeyDown(KEY_S))
    camera.transform.position =
        add3(camera.transform.position,
             localToWorldDir((float3){0, 0, -MOVE_SPEED * deltaTime},
                             &camera.transform));
  if (IsKeyDown(KEY_A))
    camera.transform.position =
        add3(camera.transform.position,
             localToWorldDir((float3){-MOVE_SPEED * deltaTime, 0, 0},
                             &camera.transform));
  if (IsKeyDown(KEY_D))
    camera.transform.position =
        add3(camera.transform.position,
             localToWorldDir((float3){MOVE_SPEED * deltaTime, 0, 0},
                             &camera.transform));

  totalTime += deltaTime;
}

void sceneStart(int argc, char **argv) {
  (void)argc;
  printf("Starting scene with %d models\n", NUM_MODELS);
  models[0] = loadOBJFile("../models/Quake_axe.obj");
  models[0]->transform = (ModelTransform){
      .pitch = 0,
      .yaw = 0,
      .roll = M_PI,
      .position = {0, 3, 25},
      .scale = 0.1f,
  };
  models[0]->texture = readPNGImage(argv[1]);
}

Frame frame;
Frame *getFrame(void) {
  // Clear frame data
  frame.data = malloc(sizeof(float3) * WINDOW_WIDTH * WINDOW_HEIGHT);
  for (int i = 0; i < WINDOW_WIDTH * WINDOW_HEIGHT; i++) {
    frame.data[i] = camera.backgroundColor;
  }

  for (int i = 0; i < NUM_MODELS; i++) {
    drawModel(models[i], &frame, &camera);
  }
  return &frame;
}
