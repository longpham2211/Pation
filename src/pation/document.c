#include<stdio.h>
#include<stdlib.h>
#include"pation/document.h"
#include<string.h>
#include<stdbool.h>
#include<math.h>

long check_size (pt_context *ctx, pt_document *doc){ 
    if ( doc -> f == NULL ){
        return ctx->sys_err = PT_SYS_IO;
    }
    if (fseek(doc->f, 0, SEEK_END) != 0){
        return ctx->sys_err = PT_SYS_IO;
    }
    doc -> size = ftell(doc -> f);
    fseek(doc -> f, 0, SEEK_SET);
    return doc -> size;
}

bool is_valid_file(pt_context *ctx, pt_document *doc){
    if (doc -> f == NULL ) {
          ctx->sys_err = PT_SYS_IO;
          return false;
    }
    char header[9];
    if(fgets(header, sizeof(header), doc -> f) == NULL){
        ctx->sys_err = PT_SYS_IO;
        return false;
    }
    char *is_pdf = header;
    char magic_byte[]  = "%PDF";
      
    if (is_pdf == NULL) return false;
    for ( int i = 0; i < strlen(magic_byte); i++){
        if ( is_pdf[i] != magic_byte[i] ){
            return false;
        }
    }
    if (fseek(doc->f, 0, SEEK_SET) != 0) return false;
    return true;
}

char *header (pt_context *ctx, pt_document *doc){ 
    if ( doc -> f == NULL ){ 
        ctx->sys_err = PT_SYS_IO;
        return "err (header_fn) -document.c";
    }
    char need_byte[9];
    char *header;
    if (fgets(need_byte, sizeof(need_byte), doc -> f) != NULL ) header = need_byte;
    else return "an occurr error\n (header_fn) -document.c";
    strncpy(doc -> header_pdf, header + 5, 3);
    doc -> header_pdf[3] = '\0';
    if (fseek(doc -> f, 0, SEEK_SET) != 0) return "err (header_fn) - document.c";
    const char *header_cp = doc->header_pdf;
    char *endptr;
    // strtod convert it to double type
    double version_now = strtod(header_cp, &endptr);
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


pt_document *pt_open_doc(pt_context *ctx, const char *file){
    pt_document *doc = (pt_document*)malloc(sizeof(*doc));
    if ( doc == NULL ){
        ctx->sys_err = PT_SYS_MEM; 
        return NULL;
    }
    doc -> f = fopen(file, "rb");
    if ( doc -> f == NULL ){
        ctx->sys_err = PT_SYS_IO;
        return NULL;
    }
    doc -> file_name = file;
    doc -> size = -1;
    doc -> close = close_doc;
    doc -> check_size = check_size;
    doc -> check_header = header;
    doc -> check_magic_byte = is_valid_file; 
    return doc;
}
