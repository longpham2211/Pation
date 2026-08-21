#include<iostream>
#include "pation/document.h"
using namespace std;

int main () {
    pt_document *doc = NULL;
    doc = pt_open_doc("../data/test.pdf");
    return 0;
}

