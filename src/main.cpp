#include<iostream>
#include "pation/document.h"
using namespace std;

int main () {
    pt_document *doc = pt_open_doc("../data/test.pdf");
    long size = doc -> check_size(doc);
    cout << "File size is: " << size << "\n";
    char *header = doc -> check_header(doc);
    printf("Version of pdf is: %s\n", header);
    bool is_pdf = doc -> check_magic_byte;
    if ( is_pdf ) printf("Valid PDF\n");
    else printf("invalid pdf\n");
    doc -> close(doc);
    return 0;
}

