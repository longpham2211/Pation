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
typedef long (find_xref_fn) (pt_document *doc, pt_structure *structure);
typedef size_t (count_page_fn) (pt_document *doc, pt_structure *structure);
typedef void (close_structure_fn) (pt_structure *structure);

struct pt_structure{
    long start_xref;
    size_t page;
    
    //vtable func
    close_structure_fn *close;
    find_xref_fn *find;

};





#ifdef __cplusplus
}
#endif
#endif
