#include<stdio.h>
#include"../include/document.h"


void load_file(const char *file_name){
    FILE *f = fopen(file_name, "rb");
    if ( f == NULL){
        printf("ERR While loading file");
        return;
    }
}

double file_size(){
    
}