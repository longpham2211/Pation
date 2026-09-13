#ifndef PARSER_H
#define PARSER_H

#ifdef __cplusplus
extern "C"{
#endif

#include "pation/context.h"
#include "pation/document.h"
#include "pation/state.h"

typedef struct pdf_parser pdf_parser;

typedef long (lookup_page_fn) (pt_context *ctx, char *content);
typedef void (main_parser_fn) (pt_context *ctx, pt_state *st);
void main_parser(pt_context *ctx, pt_state *st);

struct pdf_parser{
    lookup_page_fn *lookup_page_obj;
    main_parser_fn *main_parse;
};

#ifdef __cplusplus
}
#endif
#endif
