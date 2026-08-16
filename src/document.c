#include<stdio.h>
#include"../include/document.h"

int dem = 0;

FILE *load_file(const char *file_path){
    
    FILE *f = fopen(file_path, "rb");
    if ( f == NULL){
        printf("ERR While loading file\n");
        return NULL;
    }
    dem++;
    printf("ham nay duoc goi %d, lan\n", dem);
    return f;
}

long file_size(const char *file_path){
    FILE *f = load_file(file_path);
    if (f == NULL){
        printf("ERR While load PDF (check file size)\n");
        return -1;
    }
    fseek(f, 0, SEEK_END);
    long file_size = ftell(f);
    return file_size;
}