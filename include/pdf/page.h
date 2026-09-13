#ifndef PAGE_H
#define PAGE_H

#ifdef __cplusplus 
extern "C"{
#endif
#include "pation/state.h"
#include "pdf/xref.h"
#include "pation/context.h"
#include "pation/document.h"
#include "pdf/xref.h"
#include "stdint.h"
#include "stdbool.h"

//struct
typedef struct pdf_page pdf_page;


// main
typedef void (main_page_fn) (pt_context *ctx, pt_state *st);
void main_page(pt_context *ctx, pt_state *st);

// func
typedef int (scan_obj_fn) (pt_context *ctx, pt_state *st);

struct pdf_page{
    int test;
    //parse page
    scan_obj_fn *scan;
    main_page_fn *main;
};


#ifdef __cplusplus
}
#endif
#endif 
