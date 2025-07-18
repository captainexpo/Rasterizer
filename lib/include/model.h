#ifndef MODEL_H
#define MODEL_H

#include "datatypes.h"
#include "pngreader.h"
#include "transform.h"
#include <stdlib.h>
typedef struct {
  int ia;
  int ib;
  int ic;
  int vt[3]; // Tex coordinate indices (not used yet)
  int vn[3]; // Normal indices (not used yet)
} Face;

struct RasterizerMaterial;

typedef struct {
  ModelTransform transform;

  float3 *points;
  Face *tris;
  size_t num_triangles;
  size_t num_points;
  float2 *tex_coords;

  float4 flatColor;
  TexImage *texture; // Should support multiple textures in the future
} RasterizerModel;

#endif
