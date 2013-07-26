%{

    #include <iostream>
    #include <cstring>
    #include "json_st.hh"
    
    extern "C" 
    {
        void yyerror(const char *);
        int yylex();
        
    } 
        
    void load_string(const char *);
    void load_file(FILE*);
    
    Value* parsd = nullptr;
%}

%code requires { #include "json_st.hh" }

%union
{
    // "Pure" types
    int int_v;
    float float_v;
    bool bool_v;
    bool null_p;
    char* string_v;
    
    // Pointers to more complex classes
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
value : NUMBER_I { $$ = new Value($1); }
    | NUMBER_F { $$ = new Value($1); }
    | BOOLEAN { $$ = new Value($1); }
    | NULL_T { $$ = new Value(); }
    | string { $$ = new Value(std::string($1)); delete $1; }
    | object { $$ = new Value(*$1); delete $1; }
    | array { $$ = new Value(*$1); delete $1; }
    ;

// String rule
string : DOUBLE_QUOTED_STRING {
        // Trim string
        std::string s($1);
        s = s.substr(1, s.length()-2);
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
assignment_list: /* empty */ { $$ = new Object(); } 
    | string COLON value {
        $$ = new Object();
        $$->insert(std::make_pair(std::string($1), *$3));
        delete $1;
        delete $3;
    } 
    | assignment_list COMMA string COLON value { 
        $$->insert(std::make_pair(std::string($3), *$5));
        delete $3;
        delete $5;
    }
    ;
    
// List rule
list: /* empty */ { $$ = new Array(); }
    | value {
        $$ = new Array();
        $$->push_back(*$1);
        delete $1;
    }
    | list COMMA value { 
        $$->push_back(*$3); 
        delete $3;
    }
    ;
    
%%

int main(int argc, char **argv)
{
    int status = 1;
    
    if (argc > 1)
    {
    
        FILE* in = fopen(argv[1], "r");
    
        load_file(in);
    
        status = yyparse();
    }
    else
        status = yyparse();
    
    if (status)
        delete parsd;
    
    std::cerr << *parsd << std::endl;
    
    delete parsd;
}

void yyerror(const char *s)
{
    fprintf(stderr, "error: %s\n", s);
}