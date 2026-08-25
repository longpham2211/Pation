/*
    SMALLAB28 SOFTWARE
    ALLRIGHTS RESERVED
*/


#include "pdf/structure.h"
#include "pation/document.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>

long find_xref_table (pt_document *doc, pt_structure *structure){
    if ( doc -> f == NULL ) return -1;
    fseek(doc -> f, 0, SEEK_SET);
    fseek(doc -> f, 0, SEEK_END);
    long size = ftell(doc -> f);
    printf("size is: %ld\n", size);
    long byte_need_to_read = size - 1024;
    char eof[byte_need_to_read];
    char *content_eof = "";
    if(fgets(eof, sizeof(eof), doc -> f) != NULL) return -1;
    content_eof = eof;
    printf("CONTENT OF OEF: %s\n", byte_need_to_read);
    return size;
}



// constuctor
pt_structure *init_pt_structure(pt_document *doc){
    if ( doc == NULL ) return NULL;
    pt_structure *structure = (pt_structure*)malloc(sizeof(*structure));
    if (structure == NULL) {
        printf("NO ENOUGH SPACE WHEN mALLOC STRUCTURE\n");
        return NULL;
    }
    structure -> page = 0;
    structure -> find = find_xref_table;
    return structure;
}

