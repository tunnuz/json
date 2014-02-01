%option noyywrap yylineno nodefault
%{
    // Provided externally
    extern "C" 
    {
        int yylex();
    }
    
    // Needed for the tokens
    #include "json.tab.hh"
%}

%%

\"[^\"]*\"                              { yylval.string_v = yytext; return DOUBLE_QUOTED_STRING; }
\'[^\']*\'                              { yylval.string_v = yytext; return SINGLE_QUOTED_STRING; }
"["                                     { return SQUARE_BRACKET_L; }
"]"                                     { return SQUARE_BRACKET_R; }
"{"                                     { return CURLY_BRACKET_L; }
"}"                                     { return CURLY_BRACKET_R; }
","                                     { return COMMA; }
":"                                     { return COLON; }
\n                                      { }
[ \t]                                   { }
[-+]?[0-9]+                             { yylval.int_v = atoi(yytext); return NUMBER_I; }
[-+]?[0-9]*\.?[0-9]*([eE][-+]?[0-9]+)?  { yylval.float_v = atof(yytext); return NUMBER_F; }
true|false                              { yylval.bool_v = ( strcmp(yytext, "true") == 0 ? true : false); return BOOLEAN; }
null                                    { return NULL_T; }
.                                       {  }

%%

/** Sets the input string to the lexer */
void load_string(const char* str)
{
    yy_switch_to_buffer(yy_scan_string(str));
}

/** Sets the input file to the lexer */
void load_file(FILE* file)
{
    yyrestart(file);
}