/*
    SMALLAB28 SOFTWARE
    ALLRIGHTS RESERVED
*/


#include "pdf/structure.h"
#include "pation/document.h"
#include <stdio.h>
#include <stdlib.h>


char *find_xref_table (pt_document *doc, pt_structure *structure){
    if( doc -> f == NULL ) return "NO (find_xref)\n";
    
    char jump[6];
    fseek(doc -> f, 0, SEEK_END);
    fgets(jump ,sizeof(jump), doc -> f);
    printf("JUMP to: %s\n", jump);
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
}

