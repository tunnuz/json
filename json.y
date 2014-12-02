%{

    #include <iostream>
    #include <cstring>
    #include <stdio.h>
    #include <stdexcept>
    #include "unescape.hh"
    #include "json_st.hh"
    
    extern "C" 
    {
        void yyerror(const char *);
        int yylex();
    } 
        
    using yy_size_t = size_t;
    extern yy_size_t yyleng;
        
    void * load_string(const char *);
    void load_file(FILE*);
    JSON::Value* parsd = nullptr;
    void clean_up(void * buffer_state);
%}

%code requires { #include "json_st.hh" }

%union
{
    // "Pure" types
    long long int int_v;
    long double float_v;
    bool bool_v;
    bool null_p;
    char* string_v;
    
    // Pointers to more complex classes
    JSON::Object* object_p;
    JSON::Array* array_p;
    JSON::Value* value_p;
} 

/** Define types for union values */
%type<string_v> DOUBLE_QUOTED_STRING SINGLE_QUOTED_STRING string
%type<int_v> NUMBER_I
%type<float_v> NUMBER_F
%type<bool_v> BOOLEAN
    
/** Declare tokens */
%token COMMA COLON
%token SQUARE_BRACKET_L SQUARE_BRACKET_R
%token CURLY_BRACKET_L CURLY_BRACKET_R
%token DOUBLE_QUOTED_STRING SINGLE_QUOTED_STRING
%token NUMBER_I NUMBER_F
%token BOOLEAN
%token NULL_T

%type <object_p> object assignment_list
%type <array_p> array list
%type <value_p> value

%start json

%%

// Entry point (every JSON file represents a value)
json: value { parsd = $1; } ;

// Object rule
object: CURLY_BRACKET_L assignment_list CURLY_BRACKET_R { $$ = $2; } ;

// Array rule
array : SQUARE_BRACKET_L list SQUARE_BRACKET_R { $$ = $2; } ;

// Values rule
value : NUMBER_I { $$ = new JSON::Value($1); }
    | NUMBER_F { $$ = new JSON::Value($1); }
    | BOOLEAN { $$ = new JSON::Value($1); }
    | NULL_T { $$ = new JSON::Value(); }
    | string { $$ = new JSON::Value(std::move(std::string($1))); delete $1; }
    | object { $$ = new JSON::Value(std::move(*$1)); delete $1; }
    | array { $$ = new JSON::Value(std::move(*$1)); delete $1; }
    ;

// String rule
string : DOUBLE_QUOTED_STRING {
        // Trim string
        std::string s { $1 + 1, yyleng - 2 };

        JSON::HELPER::unescape(s);

        char* t = new char[s.length()+1];
        strcpy(t, s.c_str());
        $$ = t;
    } 
    | SINGLE_QUOTED_STRING {
        // Trim string
        std::string s($1);
        s = s.substr(1, s.length()-2);
        char* t = new char[s.length()+1];
        strcpy(t, s.c_str());
        $$ = t;
    };

// Assignments rule
assignment_list: /* empty */ { $$ = new JSON::Object(); } 
    | string COLON value {
        $$ = new JSON::Object();
        $$->insert(std::make_pair(std::string($1), std::move(*$3)));
        delete $1;
        delete $3;
    } 
    | assignment_list COMMA string COLON value { 
        $$->insert(std::make_pair(std::string($3), std::move(*$5)));
        delete $3;
        delete $5;
    }
    ;
    
// List rule
list: /* empty */ { $$ = new JSON::Array(); }
    | value {
        $$ = new JSON::Array();
        $$->push_back(std::move(*$1));
        delete $1;
    }
    | list COMMA value { 
        $$->push_back(std::move(*$3)); 
        delete $3;
    }
    ;
    
%%

namespace {

    class FileHandle {
    public:
        explicit FileHandle(const char* filename)
            :
                m_handle { fopen(filename, "r") }
        {
            if (not m_handle) {
                throw std::runtime_error("Impossible to open file.");
            }
        }

        ~FileHandle()
        {
            if (m_handle) fclose(m_handle);
        }

        operator FILE* () { return m_handle; }

        FileHandle(const FileHandle&) = delete;
        FileHandle& operator=(const FileHandle&) = delete;

    private:

        FILE* m_handle;

    };

}

JSON::Value parse_file(const char* filename)
{    
    FileHandle fh { filename };
    JSON::Value v;
    
    load_file(fh);
    int status = yyparse();
    
    if (status)
        throw std::runtime_error("Error parsing file: JSON syntax.");
    else
        v = *parsd;
    
    delete parsd;

    return v;
}

JSON::Value parse_string(const std::string& s)
{
    void * buffer_state = load_string(s.c_str());
    
    int status = yyparse();
    
    if (status)
    {
        throw std::runtime_error("Error parsing string: JSON syntax.");
        delete parsd;
    }
    else
    {
        JSON::Value v = *parsd;
        delete parsd;
        if (buffer_state) clean_up(buffer_state);
        return v;    
    }
}

void yyerror(const char *s)
{
    fprintf(stderr, "error: %s\n", s);
}
