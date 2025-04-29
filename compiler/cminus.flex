/************************************************************/
/* File:cminus.flex                                               */
/* Scanner (Lexical Analyzer) for the C-Minus Compiler       */
/*                                                          */
/* Student Name  : Klara Ehab Maher                         */
/* Course        : CS-352                                   */
/* Section       : Wednesday 3 PM                           */
/* Modification Date: April 27, 2025                        */
/*                                                          */
/* Compiler Construction: Principles and Practice          */
/* Kenneth C. Louden                                        */
/************************************************************/


#include "globals.h"
#include "util.h"
#include "scan.h"

int lineno = 1;
char tokenString[MAXTOKENLEN+1];

%}

digit       [0-9]
letter      [a-zA-Z]
identifier  {letter}({letter}|{digit})*
number      {digit}+
whitespace  [ \t\r]+
newline     \n
comment     "/*"([^*]|\*+[^*/])*\*+"/"

%option noyywrap

%%

"if"            { return IF; }
"else"          { return ELSE; }
"int"           { return INT; }
"return"        { return RETURN; }
"void"          { return VOID; }
"while"         { return WHILE; }

"=="            { return EQ; }
"!="            { return NE; }
"<="            { return LE; }
">="            { return GE; }
"<"             { return LT; }
">"             { return GT; }
"="             { return ASSIGN; }
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return TIMES; }
"/"             { return OVER; }
";"             { return SEMI; }
","             { return COMMA; }
"("             { return LPAREN; }
")"             { return RPAREN; }
"["             { return LBRACKET; }
"]"             { return RBRACKET; }
"{"             { return LBRACE; }
"}"             { return RBRACE; }

{comment}       { /* skip comments */ }
{number}        { return NUM; }
{identifier}    { return ID; }
{whitespace}    { /* skip whitespace */ }
{newline}       { lineno++; }
.               { return ERROR; }

%%

TokenType getToken(void) {
  static int firstTime = TRUE;
  TokenType currentToken;

  if (firstTime) {
    firstTime = FALSE;
    yyin = fopen("cminus.txt", "r");
    if (!yyin) {
      fprintf(stderr, "Cannot open input file\n");
      exit(1);
    }
    listing = stdout;
  }

  currentToken = yylex();
  strncpy(tokenString, yytext, MAXTOKENLEN);
  tokenString[MAXTOKENLEN] = '\0';
  
  if (TraceScan) {
    fprintf(listing, "\t%d: ", lineno);
    printToken(currentToken, tokenString);
  }

  return currentToken;
}