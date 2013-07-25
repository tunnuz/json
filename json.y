%{

    #include <iostream>
    #include "json.hh"
    using namespace std;
    
    extern "C" 
    {
        void yyerror(const char *);
        int yylex();
    } 
    
    #include "json.hh"
    
%}

%union
{
    int int_v;
    float float_v;
    char* string_v;
    bool bool_v;
} 

/** Define types for union values */
%type<string_v> key string DOUBLE_QUOTED_STRING SINGLE_QUOTED_STRING
%type<int_v> NUMBER_I
%type<float_v> NUMBER_F
%type<bool_v> BOOL
    
/** Declare tokens */
%token COMMA COLON
%token SQUARE_BRACKET_L SQUARE_BRACKET_R
%token CURLY_BRACKET_L CURLY_BRACKET_R
%token DOUBLE_QUOTED_STRING SINGLE_QUOTED_STRING
%token NUMBER_I NUMBER_F
%token BOOL

%%

/** Grammar for objects:
    
    {}
    { "foo": 1 }
    { "foo": 1, "bar": "k" }
*/

object:
    | CURLY_BRACKET_L CURLY_BRACKET_R
    | CURLY_BRACKET_L assignment_list CURLY_BRACKET_R
    ;

value : NUMBER_I
    | NUMBER_F
    | BOOL
    | string
    | object
    ;

string : DOUBLE_QUOTED_STRING
    | SINGLE_QUOTED_STRING
    ;

key: string 
    ;
    
assignment_list: key COLON value
    |   key COLON value COMMA assignment_list
    ;


%%

int main(int argc, char **argv)
{
    yyparse();
}

void yyerror(const char *s)
{
    fprintf(stderr, "error: %s\n", s);
}