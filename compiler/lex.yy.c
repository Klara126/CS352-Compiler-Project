/* lex.yy.c - Customized C-Minus lexical analyzer */

/* Flex definitions and tables - DO NOT MODIFY */
#define FLEX_SCANNER
#define YY_FLEX_MAJOR_VERSION 2
#define YY_FLEX_MINOR_VERSION 5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "util.h"
#include "scan.h"

/* Global variables */
int lineno = 1;
char tokenString[MAXTOKENLEN+1];
FILE* listing;

%{
/* User-defined variables */
int yylex(void);
void yyerror(const char*);
%}

/* Lex patterns */
DIGIT    [0-9]
LETTER   [a-zA-Z]
ID       {LETTER}({LETTER}|{DIGIT})*
NUM      {DIGIT}+
WS       [ \t\r]+
COMMENT  "/*"([^*]|\*+[^*/])*\*+"/"

%option noyywrap
%option yylineno

%%
/* Lex rules */
"if"       { return IF; }
"else"     { return ELSE; }
"int"      { return INT; }
"return"   { return RETURN; }
"void"     { return VOID; }
"while"    { return WHILE; }

"=="       { return EQ; }
"!="       { return NE; }
"<="       { return LE; }
">="       { return GE; }
"<"        { return LT; }
">"        { return GT; }
"="        { return ASSIGN; }
"+"        { return PLUS; }
"-"        { return MINUS; }
"*"        { return TIMES; }
"/"        { return OVER; }
";"        { return SEMI; }
","        { return COMMA; }
"("        { return LPAREN; }
")"        { return RPAREN; }
"["        { return LBRACKET; }
"]"        { return RBRACKET; }
"{"        { return LBRACE; }
"}"        { return RBRACE; }

{COMMENT}  { /* Skip comments */ }
{NUM}      { return NUM; }
{ID}       { return ID; }
{WS}       { /* Skip whitespace */ }
\n         { lineno++; }
.          { return ERROR; }

%%

/* Custom getToken function */
TokenType getToken(void) {
    static int firstTime = TRUE;
    TokenType currentToken;

    if (firstTime) {
        firstTime = FALSE;
        yyin = fopen("cminus.txt", "r");
        if (!yyin) {
            fprintf(stderr, "Error: Cannot open cminus.txt\n");
            exit(1);
        }
        listing = stdout;
    }

    currentToken = yylex();
    strncpy(tokenString, yytext, MAXTOKENLEN);
    tokenString[MAXTOKENLEN] = '\0';

    if (TraceScan) {
        fprintf(listing, "%4d: ", lineno);
        printToken(currentToken, tokenString);
    }

    return currentToken;
}

/* Error handler */
void yyerror(const char *s) {
    fprintf(stderr, "Line %d: %s at '%s'\n", lineno, s, yytext);
}

/* Main function */
int main(int argc, char *argv[]) {
    while (getToken() != 0) {
        /* Token processing loop */
    }
    fclose(yyin);
    return 0;
}

/* Flex-generated tables and support functions */
[... ALL ORIGINAL FLEX TABLES AND FUNCTIONS ...]