/*
    SMALLAB28 SOFTWARE
    ALLRIGHTS RESERVED
*/


#include "pdf/structure.h"
#include "pation/document.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <regex>




long find_xref_table (pt_document *doc, pt_structure *structure){
    if (doc->f == NULL ) return -1;
    fseek(doc->f, -1024, SEEK_END);

    char buffer[1024];
    size_t byte_read = fread(buffer, 1, 1024, doc -> f);
    if ( byte_read == 0 ) return -1;
    // parse xref
    std::string content(buffer, byte_read);
    size_t startContent = content.find("startxref");
    size_t endContent = content.find("%%EOF", startContent);
    std::string xref = content.substr(startContent, endContent - startContent);
    size_t find_byte_offset = xref.rfind("f");
    std::string byte_offset_string = xref.substr(find_byte_offset + 1);
    long byte_offset = std::stol(byte_offset_string);
    structure -> start_xref = byte_offset;
    return structure->start_xref;
}





int xref (pt_document *doc, pt_structure *structure){
  fseek(doc->f, 0, SEEK_SET);
  fseek(doc->f, structure->start_xref, SEEK_SET);
  char content[4];
  if (fread(content, 1, 4, doc -> f) == 0) return -1;


  std::string need_content = static_cast<std::string>(content);
  size_t start_pos = need_content.find("xref");
  std::string xref_chain = need_content.substr(start_pos, 4);


  std::cout << "content is: " << xref_chain << "\n";
  std::string pattern = "xref";


  for ( int i = 0; i < xref_chain.length(); i++){
    if (xref_chain[i] != pattern[i]){
      return -1;
    }
  }

  char object[2];
  if(fread(object, 1, 2, doc->f) == 0) return -1;
  std::string object_chain = static_cast<std::string>(object);



  int first_object = std::stol(object_chain);
  printf("The first object is: %d\n", first_object);
 

  char entry[3];
  if(fread(entry, 1, 3, doc->f) == 0) return -1;
  std::string entry_chain = static_cast<std::string>(entry);
  int first_entry = std::stol(entry_chain);
  printf("the first entry is: %d\n", first_entry);



  return 1;
}



// close constructor
void close_structure(pt_structure *structure){
    free(structure); 
}

// constuctor
pt_structure *init_pt_structure(pt_document *doc){
    if ( doc == NULL ) return NULL;
    pt_structure *structure = (pt_structure*)malloc(sizeof(*structure));
    if (structure == NULL) {
        printf("NO ENOUGH SPACE WHEN mALLOC STRUCTURE\n");
        return NULL;
    }
    structure -> page = 0;
    structure -> find = find_xref_table;
    structure -> close = close_structure;
    structure -> parse = xref;
    return structure;
}

