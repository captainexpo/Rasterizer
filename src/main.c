
#include "../include/renderer.h"
#include "../include/scene.h"
#include "../include/window.h"
#include "raylib.h"
#include <stdlib.h>
#include <time.h>

unsigned long long int frameCount = 0;

int main(int argc, char **argv) {
  srand((unsigned int)time(NULL));
  SetTraceLogLevel(LOG_ERROR);
  InitWindow(REAL_WINDOW_WIDTH, REAL_WINDOW_HEIGHT, "Rasterizer");
  SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
  sceneStart(argc, argv);
  while (!WindowShouldClose()) {
    sceneUpdate(GetFrameTime());
    initFrame(&mainCamera);
    onRender();
    renderFrame(&mainCamera);
  }
  CloseWindow();

  return 0;
}
