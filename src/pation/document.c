#include<stdio.h>
#include<stdlib.h>
#include"pation/document.h"
#include<string.h>
#include<stdbool.h>

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

bool is_valid_file(pt_document *doc){
      if (doc -> f == NULL ) {
          printf("ERR WHILE CHECKING VALID PDF\n");
          free(doc);
          return false;
      }
      char header[9];
      char *is_pdf = fgets(header, sizeof(header), doc -> f);
      if (*is_pdf != '%PDF'){
        return false;
      }
      return true;
}

char *header (pt_document *doc){ 
      if ( doc -> f == NULL ){ 
          free(doc);
          return "ERR WHILE LOAD PDF";
      }
      char need_byte[9];
      char *header;
      if ( fgets (need_byte, sizeof(need_byte), doc -> f) != NULL ) header = need_byte;
      else return "an occurr error\n";
      strncpy(doc -> header_pdf, header + 5, 3);
      doc -> header_pdf[3] = '\0';  
      fseek(doc -> f, 0, SEEK_SET);
      return doc -> header_pdf;
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
    doc -> check_header = header;
    return doc;
}
