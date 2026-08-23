#include<stdio.h>
#include<stdlib.h>
#include"pation/document.h"


long check_size (pt_document *doc){ 
      if ( doc -> f == NULL ){
          printf("ERR WHILE CHECK FILE\n");
          return -1;
      }
      fseek(doc -> f, 0, SEEK_END);
      doc -> size = ftell(doc -> f);
      fseek(doc -> f, 0, SEEK_SET);
      return doc -> size;
}


void close_doc(pt_document *doc){
    if ( doc != NULL ){
        if ( doc -> f != NULL ) {
            fclose(doc->f);
        }
    }
    free(doc);
}


pt_document *pt_open_doc(const char *file){
    pt_document *doc = (pt_document*)malloc(sizeof(*doc));
    if ( doc == NULL ){
        printf("No enough space\n");
        free(doc);
        return NULL;
    }
    doc -> f = fopen(file, "rb");
    if ( doc -> f == NULL ){
        printf("ERR WITH CONSTRUCTOR\n");
        return NULL;
    }
    doc -> file_name = file;
    doc -> size = -1;
    doc -> close = close_doc;
    doc -> check_size = check_size;
    return doc;
}
