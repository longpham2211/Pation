#ifndef DOCUMENT_H
#define DOCUMENT_H
#ifdef __cplusplus
extern "C" {
#endif

#include<stdio.h>

  //struct pt_document
typedef struct pt_document pt_document;
  
  // func pointer
typedef void (close_fn) (pt_document *doc);
typedef long (size_fn) (pt_document *doc);
typedef char *(header_fn) (pt_document *doc);
  // Constructor
pt_document *pt_open_doc(const char *file);


struct pt_document {
    FILE *f;
    const char *file_name;
    long size;
    char header_pdf[4];
    close_fn *close;
    size_fn *check_size;
    header_fn *check_header;
};


#ifdef __cplusplus
}
#endif

#endif
