#ifndef TOKEN_H
#define TOKEN_H

/*

x = $"x";
f = $"f" : (x, y) -> x^2 + y;
identity = $"I":x->x;

print(identity)
>>> I(x) = x

*/

typedef enum token_type {
    TOKEN_ERROR = -1,
    TOKEN_SYMBOL,
    TOKEN_NUMBER_LIT,
    TOKEN_STRING_LIT,

    TOKEN_ASSIGNOP,
    TOKEN_MAPOP,
    
    TOKEN_ADDOP,
    TOKEN_MULOP,
    TOKEN_EXPOP,

    TOKEN_DOLLAR,
    TOKEN_COLON,
    TOKEN_SEMICOLON,

    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACK,
    TOKEN_RBRACK,
    TOKEN_LBRACE,
    TOKEN_RBRACE
} token_type_t;

typedef struct token {
    char lexeme[LEXEME_MAX_SIZE];
    token_type_t type;
} token_t;

#endif