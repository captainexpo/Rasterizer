#ifndef PNGREADER_H
#define PNGREADER_H

/*
 * Copyright 2016 Ali Reza Barkhordari
 *
 * Code base credits to Guillaume Cottenceau, edited by Ali Reza Barkhordari
 *
 * Note: To compile using gcc you should use flag -lpng
 */

/*
 * Copyright 2002-2010 Guillaume Cottenceau.
 *
 * This software may be freely redistributed under the terms
 * of the X11 license.
 *
 */
#include "datatypes.h"
#include <stdint.h>
typedef struct {
  int rows;
  int cols;
  float3 *cmap;
} TexImage;

TexImage *readPNGImage(char *filename);
void writePPMImage(TexImage *image, char *filename);
#endif
