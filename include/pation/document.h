#ifndef DOCUMENT_H
#define DOCUMENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include<stdio.h>

//struct pt_document
typedef struct pt_document pt_docment;


// func pt_document

pt_document *pt_open_doc(const char *file_name);
void *pt_close_doc(pt_document *doc);

#ifdef __cplusplus
}
#endif

#endif
