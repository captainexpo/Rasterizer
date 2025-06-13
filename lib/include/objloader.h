#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "model.h"
RasterizerModel *loadOBJFile(const char *path);
int countSpaces(char *buf);

#endif
