%{

    #include <iostream>
    #include <cstring>
    #include "json.hh"
    
    extern "C" 
    {
        void yyerror(const char *);
        int yylex();
        
    } 
    
    #include "json.hh"
    
    void load_string(const char *);
    void load_file(FILE*);
    
    Value* parsd = nullptr;
%}

%code requires { #include "json.hh" }

%union
{
    int int_v;
    float float_v;
    char* string_v;
    bool bool_v;
    Object* object_p;
    Array* array_p;
    Value* value_p;
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

%type <object_p> object assignment_list
%type <array_p> array list
%type <value_p> value

%start json

%%

// Entry point (every JSON file represents a value)
json: value { parsd = $1; } ;

object: CURLY_BRACKET_L assignment_list CURLY_BRACKET_R 
    { 
        $$ = $2;
    }
    ;

array : SQUARE_BRACKET_L list SQUARE_BRACKET_R
    {
        $$ = $2;
    }
    ;

value : NUMBER_I 
    { 
        $$ = new Value($1); 
    }
    | NUMBER_F 
    { 
        $$ = new Value($1); 
    }
    | BOOLEAN 
    { 
        $$ = new Value($1); 
    }
    | string 
    { 
        $$ = new Value(std::string($1));     
    }
    | object 
    { 
        $$ = new Value(*$1); 
    }
    | array 
    { 
        $$ = new Value(*$1); 
    }
    ;
    
string : DOUBLE_QUOTED_STRING 
    {
        // Trim string
        std::string s($1);
        s = s.substr(1, s.length()-2);
        
        char* t = new char[s.length()+1];
        strcpy(t, s.c_str());

        $$ = t;
    } 
    | SINGLE_QUOTED_STRING
    {
        // Trim string
        std::string s($1);
        s = s.substr(1, s.length()-2);
        
        char* t = new char[s.length()+1];
        strcpy(t, s.c_str());

        $$ = t;
    };

assignment_list:
    {
        $$ = new Object();
    }
    |   string COLON value
    {
        $$ = new Object();
        $$->insert(std::make_pair($1, *$3));
    } 
    | assignment_list COMMA string COLON value 
    {
        $$->insert(std::make_pair($3, *$5));
    }
    ;

list:  
    {
        $$ = new Array();
    }
    | value
    {
        $$ = new Array();
        $$->push_back(*$1);
    }
    | list COMMA value
    {
        $$->push_back(*$3);   
    }
    ;
    
%%

int main(int argc, char **argv)
{
    FILE* in = fopen(argv[1], "r");
    
    load_file(in);
    
    int status = yyparse();
    
    // If parsing went wrong delete the object constructed so far
    if (status)
        delete parsd;
    
    std::cerr << *parsd << std::endl;
}


void yyerror(const char *s)
{
    fprintf(stderr, "error: %s\n", s);
}