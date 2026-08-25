#ifndef PARSE_H
#define PARSE_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdio.h>
#include "pation/document.h"
// Struct of page
typedef struct pt_structure pt_structure;


// Constuctor 
pt_structure *init_pt_structure(pt_document *doc);


// func
typedef char *(find_xref) (pt_document *doc, pt_structure *structure);
typedef size_t (count_page) (pt_document *doc, pt_structure *structure);


struct pt_structure{
    char startxref;
    size_t page;

    find_xref *find;
};





#ifdef __cplusplus
}
#endif
#endif
