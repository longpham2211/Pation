#pragma once

#include <iostream>
#include <string>

/* 
    The stucture of pdf
    %PDF-1.7                         <-- 1. Header 

    1 0 obj                          <-- 2. Body (object, picture, font, text)
    << /Type /Catalog /Pages 2 0 R >>
    endobj

    xref                             <-- 3. Xref Table (offset table)
    0 3
    0000000000 65535 f 
    0000000015 00000 n 

    trailer                          <-- 4. Trailer (file reading start point)
    << /Size 3 /Root 1 0 R >>
    startxref
    120
    %%EOF
*/

bool check_header(const char *file_path);

const std::string version_pdf(const char *file_path);
