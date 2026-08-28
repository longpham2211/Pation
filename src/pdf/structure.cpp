/*
    SMALLAB28 SOFTWARE
    ALLRIGHTS RESERVED
*/


#include "pdf/structure.h"
#include "pation/document.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>





long find_xref_table (pt_document *doc, pt_structure *structure){
    if (doc->f == NULL ) return -1;
    fseek(doc->f, -1024, SEEK_END);

    char buffer[1024];
    size_t byte_read = fread(buffer, 1, 1024, doc -> f);
    if ( byte_read == 0 ) return -1;
    // parse xref
    std::string content(buffer, byte_read);
    size_t startContent = content.find("startxref");
    size_t endContent = content.find("%%EOF", startContent);
    std::string xref = content.substr(startContent, endContent - startContent);
    size_t find_byte_offset = xref.rfind("f");
    std::string byte_offset_string = xref.substr(find_byte_offset + 1);
    long byte_offset = std::stol(byte_offset_string);
    structure -> start_xref = byte_offset;
    return structure->start_xref;
}



// close constructor
void close_structure(pt_structure *structure){
    free(structure); 
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
    structure -> close = close_structure;
    return structure;
}

