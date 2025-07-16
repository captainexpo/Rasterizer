
#include "../include/scene.h"
#include "raylib.h"
#include "renderer.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define REAL_WINDOW_HEIGHT GetMonitorHeight(GetCurrentMonitor())
#define REAL_WINDOW_WIDTH GetMonitorWidth(GetCurrentMonitor())

unsigned long long int frameCount = 0;

int main(int argc, char **argv) {
  printf("Starting rasterizer...\n");
  srand((unsigned int)time(NULL));
  SetTraceLogLevel(LOG_WARNING);

  InitWindow(REAL_WINDOW_WIDTH, REAL_WINDOW_HEIGHT, "Rasterizer");
  // SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
  printf("Calling sceneStart\n");
  printf("%p\n", (void *)sceneStart);
  sceneStart(argc, argv);
  while (!WindowShouldClose()) {
    BeginDrawing();
    sceneUpdate(GetFrameTime());
    initFrame(&mainCamera);
    onRender();
    renderFrame(&mainCamera, REAL_WINDOW_WIDTH, REAL_WINDOW_HEIGHT);
    onDrawUI();
    EndDrawing();
  }
  CloseWindow();

  return 0;
}
