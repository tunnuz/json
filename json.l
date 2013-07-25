%option noyywrap yylineno nodefault
%{
    #include <iostream>

    extern "C" 
    {
        int yylex();
    } 
    
    #include "json.tab.h"

%}

%%

\"[^\"]*?\"             { yylval.string_v = yytext; return DOUBLE_QUOTED_STRING; }
\'[^\']*?\'             { yylval.string_v = yytext; return SINGLE_QUOTED_STRING; }
"["                     { return SQUARE_BRACKET_L; }
"]"                     { return SQUARE_BRACKET_R; }
"{"                     { return CURLY_BRACKET_L; }
"}"                     { return CURLY_BRACKET_R; }
","                     { return COMMA; }
":"                     { return COLON; }
\n                      { }
[ \t]                   { }
[-+]?[0-9]+             { yylval.int_v = atoi(yytext); return NUMBER_I; }
[-+]?[0-9]*\.?[0-9]*    { yylval.float_v = atof(yytext); return NUMBER_F; }
true|false              { yylval.bool_v = (std::string(yytext) == "true" ? true : false); return BOOLEAN; }
.                       { printf("Unrecognized: ", yytext); }
%%
