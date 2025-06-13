#include "../include/pngreader.h"
#include <png.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

TexImage *readPNGImage(char *filename) {
  printf("[read_png_file] Reading PNG file: %s\n", filename);
  TexImage *image = malloc(sizeof(TexImage));
  png_byte color_type;
  png_bytep *row_pointers;
  png_structp png_ptr;
  png_infop info_ptr;
  int i, j;

  // 8 is the maximum size that can be checked
  char header[8];

  /* open file and test for it being a png */
  FILE *fp = fopen(filename, "rb");
  if (!fp) {
    fprintf(stderr, "[read_png_file] File %s could not be opened for reading",
            filename);
    return NULL;
  }

  fread(header, 1, 8, fp);
  if (png_sig_cmp((const unsigned char *)header, 0, 8)) {
    fprintf(stderr, "[read_png_file] File %s is not recognized as a PNG file",
            filename);
    return NULL;
  }

  /* initialize stuff */
  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_ptr) {
    fprintf(stderr, "[read_png_file] png_create_read_struct failed");
    return NULL;
  }

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    fprintf(stderr, "[read_png_file] png_create_info_struct failed");
    return NULL;
  }

  if (setjmp(png_jmpbuf(png_ptr))) {
    fprintf(stderr, "[read_png_file] Error during init_io");
  }

  png_init_io(png_ptr, fp);
  png_set_sig_bytes(png_ptr, 8);

  png_read_info(png_ptr, info_ptr);

  image->cols = png_get_image_width(png_ptr, info_ptr);
  image->rows = png_get_image_height(png_ptr, info_ptr);

  color_type = png_get_color_type(png_ptr, info_ptr);
  if (color_type != PNG_COLOR_TYPE_RGB) {
    fprintf(stderr, "[read_png_file] Only RGB PNGs are supported");
    return NULL;
  }
  png_read_update_info(png_ptr, info_ptr);

  /* read file */
  if (setjmp(png_jmpbuf(png_ptr))) {
    fprintf(stderr, "[read_png_file] Error during read_image");
    return NULL;
  }

  /* memory allocation */
  row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * image->rows);
  for (i = 0; i < image->rows; i += 1) {
    row_pointers[i] = (png_byte *)malloc(png_get_rowbytes(png_ptr, info_ptr));
  }

  image->cmap = malloc(image->cols * image->rows * sizeof(float3));

  png_read_image(png_ptr, row_pointers);
  fclose(fp);

  for (i = 0; i < image->rows; i += 1) {
    png_byte *row = row_pointers[i];
    for (j = 0; j < image->cols; j += 1) {
      png_byte *ptr = &(row[j * 3]);

      image->cmap[i * image->cols + j] =
          (float3){(float)ptr[0], (float)ptr[1], (float)ptr[2]};
    }
  }

  /* clean up */
  for (i = 0; i < image->rows; i += 1) {
    free(row_pointers[i]);
  }
  free(row_pointers);

  return image;
}
