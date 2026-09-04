#ifndef CONTEXT_H
#define CONTEXT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>


typedef struct pt_context pt_context;


// Constructor
pt_context *pt_ctx_create();
typedef void (pt_ctx_free) (pt_context *ctx);

typedef enum {
    PT_SYS_OK = 0,
    PT_SYS_IO,
    PT_SYS_MEM, 
    PT_SYS_PERMISSON,   
}pt_sys_err;

typedef enum {
    PT_DOC_OK = 0,
    PT_DOC_INVALID,
    PT_DOC_FUNC,
    PT_DOC_VAL,
    PT_DOC_FORMAT,
    PT_DOC_SYNTAX,
    PT_DOC_UNSUPPORTED, 
    PT_DOC_ENCRYPTED,
}pt_doc_err;

struct pt_context {
    pt_sys_err sys_err;
    pt_doc_err doc_err;
    // func pointer
    pt_ctx_free *free;
    int os_code;
    const char *message;
};



#ifdef __cplusplus

}
#endif
#endif

