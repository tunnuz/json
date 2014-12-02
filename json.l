%option noyywrap yylineno nodefault
%{
    // Provided externally
    extern "C" 
    {
        int yylex();
    }

	// Needed for std::stoll and std::stold
	#include <string>
    
    // Needed for the tokens
    #include "json.tab.hh"
%}

UnicodeEscapeSequence                   u[0-9A-Fa-f]{4}
JSONEscapeCharacter                     ["\\/bfnrt]
JSONEscapeSequence                      {JSONEscapeCharacter}|{UnicodeEscapeSequence}
JSONStringCharacter                     [^"\\]|\\{JSONEscapeSequence}
JSONString                              \"{JSONStringCharacter}*\"

%%

{JSONString}                            { yylval.string_v = yytext; return DOUBLE_QUOTED_STRING; }
\'[^\']*\'                              { yylval.string_v = yytext; return SINGLE_QUOTED_STRING; }
"["                                     { return SQUARE_BRACKET_L; }
"]"                                     { return SQUARE_BRACKET_R; }
"{"                                     { return CURLY_BRACKET_L; }
"}"                                     { return CURLY_BRACKET_R; }
","                                     { return COMMA; }
":"                                     { return COLON; }
\n                                      { }
[ \t]                                   { }
[-+]?[0-9]+                             { yylval.int_v = std::stoll(yytext); return NUMBER_I; }
[-+]?[0-9]*\.?[0-9]*([eE][-+]?[0-9]+)?  { yylval.float_v = std::stold(yytext); return NUMBER_F; }
true|false                              { yylval.bool_v = ( strcmp(yytext, "true") == 0 ? true : false); return BOOLEAN; }
null                                    { return NULL_T; }
.                                       {  }

%%

/** Sets the input string to the lexer */
void * load_string(const char* str)
{
    YY_BUFFER_STATE buffer_state = yy_scan_string(str);
    yy_switch_to_buffer(buffer_state);
    return buffer_state;
}

void clean_up(void *buffer_state)
{
    yy_delete_buffer(static_cast<YY_BUFFER_STATE>(buffer_state));
}

/** Sets the input file to the lexer */
void load_file(FILE* file)
{
    yyrestart(file);
}
