

#include "pation/state.h"
#include "pation/context.h"
#include "pdf/parser.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <regex>
#include <string>

long lookup_page (pt_context *ctx, char *content){
    int quantity = strlen(content);
    std::string content_page(content, quantity);
    size_t start_content = content_page.find("<<");
    size_t f_page_tok = content_page.rfind("/Pages");
    std::string page_tok = content_page.substr(f_page_tok, f_page_tok - start_content);
    std::regex page_tok_pt (R"((/Pages)\s+([0-9]+)\s+([0-9]+)\s+)");
    std::smatch match_tok;
    long page_obj = 0;
    if (std::regex_search(page_tok, match_tok, page_tok_pt)){
        page_obj = (long) std::stoi(match_tok[2]); // smatch always have match[0];
    }
    return page_obj;
}


void main_parser (pt_context *ctx, pt_state *st){
    
    st->parser->lookup_page_obj = lookup_page;
    st->parser->main_parse = main_parser;
}
