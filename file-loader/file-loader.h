#ifdef file-loader

#include<stdio.h>

typedef struct{
    const char *fileName;
    const char *path;
}fileLoader;

void file_loader(fileLoader *load);