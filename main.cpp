#include<iostream>
#include "./include/document.h"
#include "./spdf/spdf.hpp"
using namespace std;

int main (){
    const char *file_path = "data/test.pdf";
    double filesize = file_size(file_path);
    cout << "File size is: " << filesize << endl;
    std::string header = version_pdf(file_path);
    cout << "Version of pdf: " << header << endl;
    return 0;
}


