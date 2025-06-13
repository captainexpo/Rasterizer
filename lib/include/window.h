#ifndef WINDOW_H
#define WINDOW_H
#include "datatypes.h"

#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 180
#define REAL_WINDOW_WIDTH 1920
#define REAL_WINDOW_HEIGHT 1080
typedef struct {
  float3 *data;
} Frame;

int drawFrame(Frame *frame);

#endif
