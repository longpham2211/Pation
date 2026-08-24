/*
    SMALLAB28 SOFTWARE
    ALLRIGHTS RESERVED
*/


#incldue"pdf/structure.h"
#include "pation/document.h";
#include <stdio.h>



char *find_xref (pt_document *doc, pt_structure *structure){
    if( doc -> f == NULL ) return "NO (find_xref)\n";

    // to do
    // need to jump to bottom of pdf
    char start[32];
    char *bottom_of_pdf;
    if (fgets(start, sizeof(start), doc -> f) bottom_of_pdf = start;
    else return "Fail (find_xref)\n";

}



// constuctor
pt_structure *pt_structure(pt_document *doc){
    if ( doc == NULL ) return NULL;
    pt_structure *structure = (pt_structure*)malloc(sizeof(pt_structure));
    if (structure == NULL) {
        printf("NO ENOUGH SPACE WHEN mALLOC STRUCTURE\n");
        return NULL;
    }
    structure -> page = 0;
    
}

