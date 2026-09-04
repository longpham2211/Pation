/*
    SMALLAB28 SOFTWARE
    ALLRIGHTS RESERVED
*/

#include "pation/context.h"
#include "pdf/structure.h"
#include "pation/document.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <unordered_map>
#include <regex>


// to do need to improve the algorithm  
long find_xref_table (pt_context *ctx, pt_document *doc, pt_structure *structure){
    if (doc->f == NULL ){
        return ctx->sys_err = PT_SYS_IO;
    }
    
    // Just working if the xref type like old xref
    if(fseek(doc->f, -1024, SEEK_END) != 0) return ctx->sys_err = PT_SYS_IO;
    // old xref table
    char buffer[1024];
    size_t size_buffer = sizeof(buffer);
    if (fread(buffer, 1, sizeof(buffer), doc->f) < size_buffer) return ctx->sys_err = PT_SYS_IO;
    
    std::string raw_byte(buffer, sizeof(buffer));
    size_t start_rb = raw_byte.rfind("startxref");
    if(start_rb == std::string::npos) return ctx->doc_err = PT_DOC_FUNC;
    std::string old_xref = raw_byte.substr(start_rb + 9);
    long old_xref_table = std::stol(old_xref); 
    structure->start_xref = old_xref_table; 
    return structure->start_xref;
    // to do with new xref;
}


// not working if xref table type is stream type
bool valid_xref (pt_context *ctx, pt_document *doc, pt_structure *structure){
    if (fseek(doc->f, 0, SEEK_SET) != 0) return false;
    if(fseek(doc->f, structure->start_xref, SEEK_SET) != 0) return false;
    char content[4];
    if (fread(content, 1, 4, doc -> f) < 4) return false;
    std::string is_valid(content, 4);
    if (is_valid != "xref") return false;
    int object, entry;
    if (fscanf(doc->f, "%d %d", &object, &entry) != 2) return false;
    long locate_byte = ftell(doc->f);
    structure->xref_data_offset = locate_byte;
    structure->base_obj = object; 
    structure->total_entries = entry;
    return true;
}

long lookup_offset (pt_context *ctx, pt_structure *structure, int target_obj){
    int index = target_obj - structure->base_obj;
    if(index < 0 || index > structure->total_entries){
        return ctx->doc_err = PT_DOC_FUNC;
    }
    return structure->lookup[index].byte_offset;
}



int dictionary_xref (pt_context *ctx, pt_document *doc, pt_structure *structure) {
    structure->lookup = (dictionary_xref_lookup*)malloc(structure->total_entries * sizeof(dictionary_xref_lookup));
    if(structure->lookup == NULL) return ctx->sys_err = PT_SYS_MEM;

    if (valid_xref(ctx, doc, structure) == false) return ctx->doc_err = PT_DOC_FUNC;
    
    if(fseek(doc->f, 0, SEEK_SET) != 0) return ctx->sys_err = PT_SYS_IO;
    if(fseek(doc->f, structure->xref_data_offset, SEEK_SET) != 0) return ctx->sys_err = PT_SYS_IO;
    // old xref 
    for (int i = structure->base_obj; i < structure->total_entries; i++){
        long offset;
        int gen;
        char status;
        if (fscanf(doc->f, "%ld %d %c", &offset, &gen, &status) == 3){ 
            structure->lookup[i].obj_id = structure->base_obj + 1;
            structure->lookup[i].byte_offset = offset;
            structure->lookup[i].gen_num = gen;
            structure->lookup[i].status_obj = status;
            printf("Obj: %d | Offset: %ld | Status: %c\n", structure->base_obj + i, offset, status);
        }
        else {
            return ctx->sys_err = PT_SYS_IO;
        }
    }
    structure->ptr_end_xref = ftell(doc->f);
    std::cout << "end xref: " << structure->ptr_end_xref << "\n";
    // new xref 
    return structure->ptr_end_xref;
}





int parse_trailer(pt_context *ctx, pt_document *doc, pt_structure *structure){
    if(doc->f == NULL){
        return ctx->sys_err = PT_SYS_IO;
    } 
    if (fseek(doc->f, -1024, SEEK_END) != 0 ) return ctx->sys_err = PT_SYS_IO;
    char buffer[1024];
    if(fread(buffer, 1, 1024, doc->f) < 1024) return ctx->sys_err = PT_SYS_IO;
    char *raw_trailer = buffer;
    std::string trailer(raw_trailer, 1024);
    size_t start_find_root_trailer = trailer.rfind("<<");
    size_t end_find_root_trailer = trailer.rfind(">>");
    std::string main_root = trailer.substr(start_find_root_trailer, end_find_root_trailer - start_find_root_trailer);
    std::regex root_pattern (R"((/Root)\s+([0-9]+)\s+([0-9]+)\s+)");   
    /*
        how to use regex
        () is 1 group 
        [0-9] match number
        [a-z] match a-z
        [A-Z] match A-Z
        for example:
        (R"((/Root\s+)([0-9]+\s+)([0-9]+\s+))");
    */


    std::smatch match;
    int obj_num = 0, gen_num = 0;

    if(std::regex_search(main_root, match, root_pattern)){
        obj_num = std::stoi(match[2].str());
        gen_num = std::stoi(match[3].str()); // im stupid right here sorry guys
    }
    // std::stoi convert from string to int
    // std::stol convert from string to long
    structure->root_obj = obj_num;
    structure->root_gen_num = gen_num;
    return ctx->doc_err = PT_DOC_OK;
}

int jump_root_object (pt_context *ctx, pt_document *doc, pt_structure *structure){
    if (structure->root_obj == 0){
        return ctx->doc_err = PT_DOC_VAL;
    }
    int jump = lookup_offset(ctx, structure, structure->root_obj);
    if (fseek(doc->f, jump, SEEK_SET) != 0) return ctx->sys_err = PT_SYS_IO;
    char buffer[45];
    if(fread(buffer, 1, 45, doc->f) < 45) return ctx->sys_err = PT_SYS_IO;
    printf("[debug] buffer jump: %s\n", buffer);
    return ctx->doc_err = PT_DOC_OK;
}


int main_function (pt_context *ctx, pt_document *doc, pt_structure *structure){
    int a = parse_trailer(ctx, doc, structure);
    int b = dictionary_xref(ctx, doc, structure);
    int c = jump_root_object(ctx, doc, structure);
    return ctx->sys_err = PT_SYS_OK;
}

// close constructor
void close_structure(pt_structure *structure){
    if (structure != NULL) {
        if (structure->lookup != NULL){
            free(structure->lookup);
         }
         free(structure);
    }
}

// constuctor
pt_structure *init_pt_structure(pt_context *ctx, pt_document *doc){
    if ( doc == NULL ) {
        ctx->sys_err = PT_SYS_IO;
        return NULL;
    }
    pt_structure *structure = (pt_structure*)malloc(sizeof(*structure));
    if (structure == NULL) {
        ctx->sys_err = PT_SYS_MEM;
        return NULL;
    }
    structure -> root_obj = 0;
    structure -> page = 0;
    structure -> find = find_xref_table;
    structure -> close = close_structure;
    structure -> is_valid_xref = valid_xref;
    structure -> dictionary = dictionary_xref;
    structure -> trailer =  parse_trailer;
    structure -> jump = jump_root_object;
    structure -> main= main_function;
    return structure;
}

