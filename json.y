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

%union
{
    int int_v;
    float float_v;
    char* string_v;
    bool bool_v;
    std::map<std::string, Value>* object_p;
    Value* value_p;
} 


/** Define types for union values */
%type<string_v> key string DOUBLE_QUOTED_STRING SINGLE_QUOTED_STRING
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
%type <value_p> value
    

%%

/** Grammar for objects:
    
    {}
    { "foo": 1 }
    { "foo": 1, "bar": "k" }
*/

object: CURLY_BRACKET_L CURLY_BRACKET_R { $$ = new Object(); }
    | CURLY_BRACKET_L assignment_list CURLY_BRACKET_R { $$ = $2; }
    ;

value : NUMBER_I { $$ = new Value($1); }
    | NUMBER_F { $$ = new Value($1); }
    | BOOLEAN { $$ = new Value($1); }
    | string { $$ = new Value($1); }
    | object { $$ = new Value($1); }
    ;

string : DOUBLE_QUOTED_STRING { $$ = $1; }
    | SINGLE_QUOTED_STRING { $$ = $1; }
    ;

key: string 
    ;
    
assignment_list: 
    key COLON value 
    {
        $$ = new Object();
        $$->insert( std::make_pair($1, Value($3) ));
    }
    | key COLON value COMMA assignment_list 
    {
        $$ = $5;
        $$->insert( std::make_pair($1, Value($3) ));
    }
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