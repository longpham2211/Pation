#include "spdf.hpp"
#include "document.h"
#include <stdio.h>
#include <string>

bool check_header(const char *file_path){
    FILE *f = load_file(file_path);
    if ( f == NULL) {
        printf("Read header failed: ERR");
        return false;
    }
    std::string magic_byte;
    char header[32];
    char *magic = fgets(header, sizeof(header), f);

    if (magic != NULL) magic_byte =  magic;
    else return false;

    size_t locate_magic_byte = magic_byte.find("%PDF-");
    if ( locate_magic_byte != std::string::npos){
        return true;
    }
    else {
        return false;
    }
}

const std::string version_pdf(const char *file_path){
    FILE *f = load_file(file_path);
    if ( f == NULL) {
        printf("Read header failed: ERR");
        return "ERROR WHEN LOADING PDF";
    }
    char ver[32];
    std::string version;
    if (check_header(file_path)){
        char *casting = fgets(ver, sizeof(ver), f);
        if(casting != NULL) version = casting;
        else return "error while read magic byte";
    }
    size_t start_version = version.find("%PDF-");
    std::string version_of_pdf = version.substr(start_version + 5);
    return version_of_pdf;
}