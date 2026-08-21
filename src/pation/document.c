#include<stdio.h>
#include<stdlib.h>
#include"pation/document.h"


struct pt_document{
    FILE *f;
    const char *file_name;
};



pt_document *pt_open_doc(const char *file_name){

     pt_document *real_doc = malloc(sizeof(pt_document));
     if (!real_doc) return NULL;

     real_doc->file_name = doc->file_name;
     
     real_doc->f = fopen(real_doc->file_name, "rb");
     if(real_doc->f == NULL){
        return NULL;
     }
     
     fseek(real_doc->f, 0, SEEK_END);
     long file_size = ftell(real_doc->f);
     
     printf("Dung luong cua file la: %ld", file_size);
     
     return real_doc;
}


