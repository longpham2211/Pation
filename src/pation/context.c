#include "pation/context.h"
#include <stdio.h>
#include <stdlib.h>



void pt_ctx_free_fn(pt_context *ctx){
    if (ctx != NULL) free(ctx);
}


pt_context *pt_ctx_create(void){
    pt_context *ctx = (pt_context*)malloc(sizeof(pt_context));
    if(ctx == NULL){
        return NULL;
    }
    ctx->message = "success";
    ctx->doc_err = PT_DOC_OK;
    ctx->sys_err = PT_SYS_OK;
    ctx->os_code = 0;
    ctx->free = pt_ctx_free_fn;
    return ctx;
}

