#include<iostream>
#include "pation/document.h"
#include "pdf/structure.h"
#include "pation/context.h"
using namespace std;

int main () {
    pt_context *ctx = pt_ctx_create();
#ifdef _WIN32
    pt_document *doc = pt_open_doc(ctx,"C:\\Pation\\data\\a.pdf");
#elif __APPLE__
    pt_document *doc = pt_open_doc(ctx,"../data/test.pdf");
#else
    pt_document *doc = pt_open_doc(ctx,"../data/test.pdf");
#endif
    pt_structure *structure = init_pt_structure(ctx, doc);  
    long size = doc -> check_size(ctx,doc);
    cout << "File size is: " << size << "\n";
    char *header = doc -> check_header(ctx,doc);
    printf("Version of pdf is: %s\n", header);
    bool is_pdf = doc -> check_magic_byte(ctx, doc);
    if ( is_pdf ) printf("Valid PDF\n");
    else printf("invalid pdf\n");
    long xref = structure -> find(ctx, doc, structure) ;
    printf("Byte offset of xref table: %ld\n", xref);
    bool parse_xref = structure -> parse(ctx, doc, structure);
    if (parse_xref){
      printf("valid pdf\n");
    }
    else printf("Invalid pdf\n");
    int dictionary = structure-> dictionary(ctx, doc, structure);
    printf("dictionary xref: %d\n", dictionary);
    printf("Byte offset of xref table: %ld\n", xref);
    doc -> close(doc);
    structure -> close(structure);
    ctx -> free(ctx);
    return 0;
}

