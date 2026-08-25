#include<iostream>
#include "pation/document.h"
#include "pdf/structure.h"
using namespace std;

int main () {
#ifdef _WIN32
    pt_document *doc = pt_open_doc("C:\\Pation\\data\\test.pdf");
#elif __APPLE__
    pt_document *doc = pt_open_doc("../data/test.pdf");
#else
    pt_document *doc = pt_open_doc("../data/test.pdf");
#endif
    pt_structure *structure = init_pt_structure(doc); 
    long size = doc -> check_size(doc);
    cout << "File size is: " << size << "\n";
    char *header = doc -> check_header(doc);
    printf("Version of pdf is: %s\n", header);
    bool is_pdf = doc -> check_magic_byte(doc);
    if ( is_pdf ) printf("Valid PDF\n");
    else printf("invalid pdf\n");
    char *xref = structure -> find(doc, structure) ;
    printf("DEBUG: %s\n", xref);
    doc -> close(doc);
    return 0;
}

