#ifndef WINDOW_H
#define WINDOW_H
#include "datatypes.h"

#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 180
typedef struct {
  float3 *data;
} Frame;

int drawFrame(Frame *frame, int winWidth, int winHeight);

#endif
