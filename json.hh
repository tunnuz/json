#ifndef JSON_HH
#define JSON_HH

#include "json_st.hh" // JSON syntax tree
#include "json.tab.h" // parser

//extern "C"
//{    
    Value parse_file(const char* filename);
    Value parse_string(const std::string& s);
//}

#endif