
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/renderer.h"
#include "../include/scene.h"
#include "../include/window.h"
#include "raylib.h"

unsigned long long int frameCount = 0;

int main(int argc, char **argv) {
  srand((unsigned int)time(NULL));
  SetTraceLogLevel(LOG_ERROR);
  InitWindow(REAL_WINDOW_WIDTH, REAL_WINDOW_HEIGHT, "Rasterizer");
  SetTargetFPS(60);

  sceneStart(argc, argv);

  char textBuffer[64];

  while (!WindowShouldClose()) {
    initFrame();
    Frame *frame = getFrame();
    BeginDrawing();
    sceneUpdate(GetFrameTime());
    drawFrame(frame);
    sprintf(textBuffer, "FPS: %d", (int)GetFPS());
    DrawText(textBuffer, 10, 10, 20, WHITE);
    EndDrawing();
    frameCount++;
    free(frame->data);
  }
  CloseWindow();
  return 0;
}
