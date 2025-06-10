#include "../include/objloader.h"
#include <ctype.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
typedef struct StringNode {
  char *buf;
  struct StringNode *next;
} StringNode;

bool isOnlyWhitespace(char *str) {
  for (; *str != 0; str++) {
    if (!isspace((unsigned char)*str))
      return false;
  }
  return true;
}

float3 parseVertex(char *buf) {
  float3 e;
  buf += 2;
  // in this format:
  //<float> <float> <float>
  // assume one space
  sscanf(buf, "%f %f %f", &e.x, &e.y, &e.z);
  return e;
}
typedef struct {
  int vIndex, tIndex, nIndex;
} ObjPoint;

int parseTriangle(char *buf, Face **fan) {
  buf += 2; // skip "f "
  int numPoints = countSpaces(buf) + 1;
  Face *faces =
      malloc(sizeof(Face) * numPoints - 2); // subtract 2 for the first triangle
  *fan = faces;
  ObjPoint points[numPoints];
  int i = 0;
  for (char *tok = strtok(buf, " "); tok != NULL; tok = strtok(NULL, " ")) {
    sscanf(tok, "%d/%d/%d", &points[i].vIndex, &points[i].tIndex,
           &points[i].nIndex);
    i++;
  }
  for (int i = 2; i < numPoints; i++) {
    Face *face = &faces[i - 2];
    face->ia = points[0].vIndex - 1; // OBJ indices are 1-based
    face->ib = points[i - 1].vIndex - 1;
    face->ic = points[i].vIndex - 1;
    face->vt[0] = points[0].tIndex - 1;
    face->vt[1] = points[i - 1].tIndex - 1;
    face->vt[2] = points[i].tIndex - 1;
  }

  return numPoints - 2; // Return number of triangles created
}

float2 parseTexCoord(char *buf) {
  float2 e;
  // in this format:
  //<float> <float>
  // assume one space
  sscanf(buf, "vt %f %f", &e.x, &e.y);
  return e;
}

int countSpaces(char *buf) {
  int spaces = 0;
  for (; *buf != '\0'; buf++)
    if (isspace(*buf))
      spaces++;
  return spaces;
}

RasterizerModel *parseFile(char buf[]) {
  RasterizerModel *model = malloc(sizeof(RasterizerModel));
  int numVerts = 0;
  int numTriangles = 0;
  int numTexCoords = 0;

  StringNode *head = NULL, *tail = NULL;
  for (char *tok = strtok(buf, "\n"); tok != NULL; tok = strtok(NULL, "\n")) {
    if (isOnlyWhitespace(tok))
      continue;

    if (tok[0] == 'v' && tok[1] == ' ') // Vertex line
      numVerts++;
    else if (tok[0] == 'f') {
      int tris =
          countSpaces(tok + 2) + 1 -
          2; // Count number of triangles, subtract 2 for the first triangle
      numTriangles += tris;
    } else if (tok[0] == 'v' && tok[1] == 't') // Texture coordinate line
      numTexCoords++;
    else if (tok[0] == '#') // Comment line
      continue;
    else if (tok[0] == 'o' || tok[0] == 'g') // Object or group name, ignore
      continue;
    else if (tok[0] == 's') // Smooth shading, ignore
      continue;
    else
      continue; // Ignore other lines
    StringNode *node = malloc(sizeof(StringNode));
    node->buf = tok;
    node->next = NULL;

    if (!head) {
      head = tail = node;
    } else {
      tail->next = node;
      tail = node;
    }
  }

  model->points = (float3 *)malloc(sizeof(float3) * numVerts);
  model->tris = (Face *)malloc(sizeof(Face) * numTriangles);
  model->tex_coords = (float2 *)malloc(sizeof(float2) * numTexCoords);
  long currentVert = 0;
  long currentTriangle = 0;
  long currentTexCoord = 0;
  do {

    if (head->buf[0] == 'f') {
      Face *fan = NULL;
      int numTris = parseTriangle(head->buf, &fan);
      for (int i = 0; i < numTris; i++) {
        model->tris[currentTriangle + i] = fan[i];
      }
      currentTriangle += numTris;
    } else if (head->buf[0] == 'v' && head->buf[1] == ' ') {
      model->points[currentVert] = parseVertex(head->buf);
      currentVert++;
    } else if (head->buf[0] == 'v' && head->buf[1] == 't') {
      model->tex_coords[currentTexCoord] = parseTexCoord(head->buf);
      currentTexCoord++;
    }
    StringNode *nhead = head->next;
    free(head);
    head = nhead;
  } while (head != NULL);

  model->num_points = numVerts;
  model->num_triangles = numTriangles;

  return model;
}

RasterizerModel *loadOBJFile(const char *path) {
  FILE *f;
  f = fopen(path, "r");

  if (f == NULL) {
    printf("Not able to open the file.");
    return NULL;
  }

  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0, SEEK_SET); /* same as rewind(f); */

  char *string = malloc(fsize + 1);
  fread(string, fsize, 1, f);
  fclose(f);

  string[fsize] = 0;

  // Parse the .obj file
  RasterizerModel *m = parseFile(string);
  free(string);
  return m;
}
