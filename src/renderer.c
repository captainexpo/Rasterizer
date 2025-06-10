#include "../include/renderer.h"
#include "../include/datatypes.h"
#include "../include/model.h"
#include "../include/transform.h"
#include "../include/utils.h"
#include <math.h>
#include <stdio.h>

float clamp(float value, float min, float max) {
  if (value < min)
    return min;
  if (value > max)
    return max;
  return value;
}

float3 getColorAtPoint(RasterizerModel *model, float2 texCoord) {
  int cols = model->texture->cols;
  int rows = model->texture->rows;

  int x = ((int)(texCoord.x * cols) % cols + cols) % cols;
  int y = ((int)(texCoord.y * rows) % rows + rows) % rows;
  if (x < 0 || y < 0) {
    printf("Invalid texture coordinates: (%d, %d) for texture size (%d, %d) "
           "(%f, %f)\n",
           x, y, cols, rows, texCoord.x, texCoord.y);
  }
  float3 pixel = model->texture->cmap[y * model->texture->rows + x];
  return pixel;
}

float depthBuffer[WINDOW_HEIGHT][WINDOW_WIDTH];

void initFrame(void) {
#pragma omp parallel for collapse(2)
  for (int i = 0; i < WINDOW_HEIGHT; i++) {
    for (int j = 0; j < WINDOW_WIDTH; j++) {
      depthBuffer[i][j] = INFINITY;
    }
  }
}
float3 toLocalPoint(float3 world, RasterizerCamera *camera) {
  float3 relative = sub3(world, camera->transform.position);

  float cy = cosf(-camera->transform.yaw), sy = sinf(-camera->transform.yaw);
  float cp = cosf(-camera->transform.pitch),
        sp = sinf(-camera->transform.pitch);
  float cr = cosf(-camera->transform.roll), sr = sinf(-camera->transform.roll);

  // Yaw (Y axis)
  float3 yawed = {cy * relative.x + sy * relative.z, relative.y,
                  -sy * relative.x + cy * relative.z};

  // Pitch (X axis)
  float3 pitched = {yawed.x, cp * yawed.y - sp * yawed.z,
                    sp * yawed.y + cp * yawed.z};

  // Roll (Z axis)
  float3 rolled = {cr * pitched.x - sr * pitched.y,
                   sr * pitched.x + cr * pitched.y, pitched.z};

  return rolled;
}

float2 getTexCoord(float3 weights, RasterizerModel *model, Face *tri,
                   float3 vertexDepths) {
  float2 a = model->tex_coords[tri->vt[0]];
  float2 b = model->tex_coords[tri->vt[1]];
  float2 c = model->tex_coords[tri->vt[2]];

  float w0 = weights.x / vertexDepths.x;
  float w1 = weights.y / vertexDepths.y;
  float w2 = weights.z / vertexDepths.z;

  float invZ = w0 + w1 + w2;

  float2 texCoord;
  texCoord.x = (a.x * w0 + b.x * w1 + c.x * w2) / invZ;
  texCoord.y = (a.y * w0 + b.y * w1 + c.y * w2) / invZ;

  return texCoord;
}
float edgeFunc(float2 a, float2 b, float2 p);
inline float edgeFunc(float2 a, float2 b, float2 p) {
  return (p.x - a.x) * (b.y - a.y) - (p.y - a.y) * (b.x - a.x);
}
void drawModel(RasterizerModel *model, Frame *frame, RasterizerCamera *camera) {

#pragma omp parallel for
  for (size_t i = 0; i < model->num_triangles; i++) {
    // printf("Drawing triangle %d\n", i);
    Face tri = model->tris[i];
    float3 world_a = toWorldPoint(&model->transform, model->points[tri.ia]);
    float3 world_b = toWorldPoint(&model->transform, model->points[tri.ib]);
    float3 world_c = toWorldPoint(&model->transform, model->points[tri.ic]);

    float3 view_a = toLocalPoint(world_a, camera);
    float3 view_b = toLocalPoint(world_b, camera);
    float3 view_c = toLocalPoint(world_c, camera);

    float3 a = worldPointToScreen(camera, view_a);
    float3 b = worldPointToScreen(camera, view_b);
    float3 c = worldPointToScreen(camera, view_c);

    if (a.z <= 0.0001f || b.z <= 0.0001f || c.z <= 0.0001f) {
      // printf("Skipping triangle %d due to backface culling\n", i);
      continue; // Skip triangles that are behind the camera
    }

    // Backface culling
    float3 ab = sub3(b, a);
    float3 ac = sub3(c, a);
    float crossZ = ab.x * ac.y - ab.y * ac.x;
    if (crossZ > 0)
      continue; // or > 0 depending on winding

    float minx = min(min(a.x, b.x), c.x);
    float maxx = max(max(a.x, b.x), c.x);
    float miny = min(min(a.y, b.y), c.y);
    float maxy = max(max(a.y, b.y), c.y);

    // Containment check
    int startx = clamp((int)minx, 0, WINDOW_WIDTH - 1);
    int starty = clamp((int)miny, 0, WINDOW_HEIGHT - 1);
    int endx = clamp((int)maxx, 0, WINDOW_WIDTH - 1);
    int endy = clamp((int)maxy, 0, WINDOW_HEIGHT - 1);
    if (minx >= WINDOW_WIDTH || maxx < 0 || miny >= WINDOW_HEIGHT || maxy < 0) {
      continue;
    }

    // Triangle screen-space vertices
    float2 p0 = truncate32(a);
    float2 p1 = truncate32(b);
    float2 p2 = truncate32(c);

    // Precompute edge constants
    float2 v0 = p0, v1 = p1, v2 = p2;

    float area = edgeFunc(v0, v1, v2);
    if (area == 0)
      continue; // Degenerate

    for (int y = starty; y <= endy; y++) {
      for (int x = startx; x <= endx; x++) {
        float2 p = {x + 0.5f, y + 0.5f}; // center of pixel

        float w0 = edgeFunc(v1, v2, p);
        float w1 = edgeFunc(v2, v0, p);
        float w2 = edgeFunc(v0, v1, p);

        if (w0 >= 0 && w1 >= 0 && w2 >= 0) {
          w0 /= area;
          w1 /= area;
          w2 /= area;
          float3 weights = {w0, w1, w2};

          float3 depths = {a.z, b.z, c.z};
          float depth = dot3(depths, weights);
          if (depthBuffer[y][x] < depth)
            continue;
          depthBuffer[y][x] = depth;

          float2 texCoord = getTexCoord(weights, model, &tri, depths);
          float3 color = getColorAtPoint(model, texCoord);
          frame->data[x + y * WINDOW_WIDTH] = color;
        }
      }
    }
  }
}

float3 worldPointToScreen(RasterizerCamera *camera, float3 point) {
  float3 cameraSpace = point;

  if (cameraSpace.z <= 0.0001f) {
    return (float3){-9999, -9999, cameraSpace.z};
  }

  float floatWindowHeight = (float)WINDOW_HEIGHT;
  float focal =
      (floatWindowHeight * 0.5f) / tanf((camera->FOV * M_PI / 180.0f) * 0.5f);

  float invZ = 1.0f / cameraSpace.z;
  float rawX = cameraSpace.x * invZ;
  float rawY = cameraSpace.y * invZ;

  float screenX = rawX * focal + ((float)WINDOW_WIDTH * 0.5f);
  float screenY = rawY * focal + ((float)WINDOW_HEIGHT * 0.5f);

  return (float3){screenX, screenY, cameraSpace.z};
}
