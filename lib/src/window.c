#include "../include/window.h"
#include "raylib.h"
#include "stdlib.h"
#include <stdio.h>

Color float3ToColor(float3 in) {
  return (Color){
      (unsigned char)in.x,
      (unsigned char)in.y,
      (unsigned char)in.z,
      255,
  };
}
Texture2D tex;
int drawFrame(Frame *frame) {
  UnloadTexture(tex); // Unload the texture
  float3 *fd = frame->data;

  // Allocate and fill color data
  Color *colorData = malloc(sizeof(Color) * WINDOW_WIDTH * WINDOW_HEIGHT);
  if (colorData == NULL)
    return 1;

  for (int y = 0; y < WINDOW_HEIGHT; y++) {
    for (int x = 0; x < WINDOW_WIDTH; x++) {
      int idx = x + y * WINDOW_WIDTH; // FIXED indexing
      colorData[idx] = float3ToColor(fd[idx]);
    }
  }

  // Create image and texture
  Image img = {.data = colorData,
               .width = WINDOW_WIDTH,
               .height = WINDOW_HEIGHT,
               .mipmaps = 1,
               .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};

  tex = LoadTextureFromImage(img);

  // Draw the texture to the screen

  DrawTextureEx(tex, (Vector2){0, 0}, 0,
                (float)REAL_WINDOW_HEIGHT / WINDOW_HEIGHT, WHITE);

  free(colorData);
  return 0;
}
