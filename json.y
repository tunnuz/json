%{

    #include <iostream>
    #include "json.hh"
    
    extern "C" 
    {
        void yyerror(const char *);
        int yylex();
    } 
    
    #include "json.hh"
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

%%

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
        $$ = new Value($1);     
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
        std::string s($1);
        $$ = const_cast<char*>(s.substr(1, s.length()-2).c_str());
    } 
    | SINGLE_QUOTED_STRING
    {
        std::string s($1);
        $$ = const_cast<char*>(s.substr(1, s.length()-2).c_str());
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

%%

int main(int argc, char **argv)
{
    int t = yyparse();
    std::cerr << t << std::endl;
}

void yyerror(const char *s)
{
    fprintf(stderr, "error: %s\n", s);
}