#ifndef PARSE_H
#define PARSE_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdio.h>
#include <stdbool.h>
#include "pation/document.h"
#include "pation/context.h"
// Struct of page
typedef struct pt_structure pt_structure;


// Constuctor 
pt_structure *init_pt_structure(pt_context *ctx, pt_document *doc);




// func
typedef long (find_xref_fn) (pt_context *ctx, pt_document *doc, pt_structure *structure);
typedef size_t (count_page_fn) (pt_context *ctx, pt_document *doc, pt_structure *structure);
typedef void (close_structure_fn) (pt_structure *structure);
typedef bool (is_valid_xref_fn) (pt_context *ctx, pt_document *doc, pt_structure *structure);
typedef int (dictionary_xref_fn) (pt_context *ctx, pt_document *doc, pt_structure *structure);
typedef int (parse_trailer_fn) (pt_context *ctx, pt_document *doc, pt_structure *structure);
typedef int (main_pation_fn) (pt_context *ctx, pt_document *doc, pt_structure *structure);
typedef long (lookup_offset_fn) (pt_context *ctx, pt_structure *structure, int target_obj);

// dictionary
typedef struct {
  int obj_id;
  long byte_offset;
  int gen_num;
  char status_obj;
}dictionary_xref_lookup; // --> lookup pointer


struct pt_structure{
    long start_xref;
    long ptr_end_xref;


    size_t page;

    int base_obj, total_entries; 
    long xref_data_offset; // xref table exclude obj && ent

    //vtable func
    close_structure_fn *close;
    find_xref_fn *find;
    is_valid_xref_fn *parse;
    dictionary_xref_fn *dictionary; 
    dictionary_xref_lookup *lookup;
    parse_trailer_fn *trailer;
    main_pation_fn *main;
};

#ifdef __cplusplus
}
#endif
#endif
