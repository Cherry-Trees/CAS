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
    TOKEN_EOF,
    TOKEN_SYMBOL,
    TOKEN_NUMBER_LIT,
    TOKEN_STRING_LIT,

    TOKEN_ASSIGN_OP,
    TOKEN_MAP_OP,
    
    TOKEN_ADD_OP,
    TOKEN_MUL_OP,
    TOKEN_EXP_OP,
    TOKEN_REL_OP,
    TOKEN_NOT_OP,

    TOKEN_DOLLAR,
    TOKEN_ELLIPSE,
    TOKEN_DOT,
    TOKEN_COMMA,
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
    int length;
    token_type_t type;
} token_t;

#endif