#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "util.h"
#include "scan.h"

/* Global variables */
int TraceScan = 1;  /* Set to 1 to enable token tracing */
int EchoSource = 1; /* Set to 1 to echo source input */

/* Function prototypes */
void printToken(TokenType, const char*);

int main(int argc, char* argv[]) {
    FILE* input;
    char inputPath[100];
    
    /* Get input file path */
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input-file>\n", argv[0]);
        exit(1);
    }
    snprintf(inputPath, sizeof(inputPath), "%s", argv[1]);

    /* Open input file */
    input = fopen(inputPath, "r");
    if (!input) {
        fprintf(stderr, "Error: Cannot open file %s\n", inputPath);
        exit(1);
    }

    /* Initialize scanner */
    lineno = 1;
    listing = stdout;
    yyin = input;

    if (EchoSource) {
        printf("\n----- Source Code -----\n");
        char line[256];
        rewind(input);
        while (fgets(line, sizeof(line), input) {
            printf("%4d: %s", lineno, line);
            lineno++;
        }
        printf("----------------------\n\n");
        rewind(input);
        lineno = 1;
    }

    /* Tokenize and print tokens */
    printf("----- Token Stream -----\n");
    TokenType token;
    while ((token = getToken()) != ENDFILE) {
        if (token == ERROR) {
            fprintf(stderr, "Lexical error at line %d: Invalid token '%s'\n", 
                    lineno, tokenString);
            exit(1);
        }
    }
    printf("-----------------------\n");

    fclose(input);
    return 0;
}

/* Print token with formatting */
void printToken(TokenType token, const char* tokenString) {
    switch (token) {
        case IF:
        case ELSE:
        case INT:
        case RETURN:
        case VOID:
        case WHILE:
            printf("reserved word: %s\n", tokenString);
            break;
        case ASSIGN: printf("=\n"); break;
        case EQ: printf("==\n"); break;
        case NE: printf("!=\n"); break;
        case LT: printf("<\n"); break;
        case LE: printf("<=\n"); break;
        case GT: printf(">\n"); break;
        case GE: printf(">=\n"); break;
        case PLUS: printf("+\n"); break;
        case MINUS: printf("-\n"); break;
        case TIMES: printf("*\n"); break;
        case OVER: printf("/\n"); break;
        case LPAREN: printf("(\n"); break;
        case RPAREN: printf(")\n"); break;
        case LBRACKET: printf("[\n"); break;
        case RBRACKET: printf("]\n"); break;
        case LBRACE: printf("{\n"); break;
        case RBRACE: printf("}\n"); break;
        case SEMI: printf(";\n"); break;
        case COMMA: printf(",\n"); break;
        case NUM:
            printf("NUM, value= %s\n", tokenString);
            break;
        case ID:
            printf("ID, name= %s\n", tokenString);
            break;
        case ERROR:
            printf("ERROR: %s\n", tokenString);
            break;
        default:
            printf("Unknown token: %d\n", token);
    }
}