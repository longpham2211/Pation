#ifndef DOCUMENT_H
#define DOCUMENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include<stdio.h>

FILE *load_file(const char *file_path);
long file_size(const char *file_path);

#ifdef __cplusplus
}
#endif

#endif