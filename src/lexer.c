#include "include/lexing/lexer.h"

#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>



static const char *tokenStrings[LEX_TOKEN_NUM_TOKEN_STRINGS] = {
    "EOF",
    "ID",
    "COLON",
    "SEMICOLON", // Instruction delimiter.
    "COMMA",
    "LPAREN",
    "RPAREN",
    "LBRACK",
    "RBRACK",
    "LBRACE",
    "RBRACE",
    "ELLIPSE",

    "INT_LIT",
    "REAL_LIT",
    "STRING_LIT",
    "INT",
    "REAL",
    "IF",
    "ELSE",
    "FOR",
    "IN",
    "WHILE",
    "CALL",
    "PROCEDURE",
    "ENDIF",
    "ENDFOR",
    "ENDWHILE",
    "ENDPROCEDURE",

    "ASSIGN_OP",
    "ADD_OP",
    "MUL_OP",
    "EXP_OP",
    "NOT_OP",
    "REL_OP",
    "AND_OP",       
    "OR_OP",
};

static int dfa[256][256];
static bool dfaConstructed = 0;
static int lineno = 1;
static char *keywords[LEX_TOKEN_NUM_KEYWORDS] = {
    "int",
    "real",
    "if",
    "else",
    "for",
    "in",
    "while",
    "procedure",
    "endif",
    "endfor",
    "endwhile",
    "endprocedure",
    "call",
};

void init_dfa(int dfa[256][256]) {

    for (int i = 0; i < 256; i++)
        for (int j = 0; j < 256; j++)
            dfa[i][j] = -1;
    
    // Symbol (1)
    for (char ch = 'A'; ch <= 'Z'; ch++) dfa[0][ch] = 1;
    for (char ch = 'a'; ch <= 'z'; ch++) dfa[0][ch] = 1;
    dfa[0]['_'] = 1;
    for (char ch = 'A'; ch <= 'Z'; ch++) dfa[1][ch] = 1;
    for (char ch = 'a'; ch <= 'z'; ch++) dfa[1][ch] = 1;
    for (char ch = '0'; ch <= '9'; ch++) dfa[1][ch] = 1;
    dfa[1]['_'] = 1;

    // Number Literal (2, 4, 5)
    for (char ch = '1'; ch <= '9'; ch++) dfa[0][ch] = 2;
    for (char ch = '0'; ch <= '9'; ch++) dfa[2][ch] = 2;
    dfa[2]['.'] = 3;
    for (char ch = '0'; ch <= '9'; ch++) dfa[3][ch] = 4;
    for (char ch = '0'; ch <= '9'; ch++) dfa[4][ch] = 4;
    dfa[0]['0'] = 5;
    dfa[5]['.'] = 3;

    // String Literal (7)
    dfa[0]['\"'] = 6;
    for (int i = 0; i < 256; i++) dfa[6][i] = 6;
    dfa[6]['\"'] = 7;

    // Colon (8)
    dfa[0][':'] = 8;

    // Semicolon (9)
    dfa[0][';'] = 9;

    // Assign Op (10)
    dfa[0]['='] = 10;

    // Add Op (11, 12)
    dfa[0]['$'] = 11;
    dfa[0]['+'] = 12;
    dfa[0]['-'] = 13;

    // Map Op (13)
    dfa[13]['>'] = 14;
    // for (char ch = '1'; ch <= '9'; ch++) dfa[1][ch] = 2;
    // dfa[11]['0'] = 5;

    // Mul Op (14)
    dfa[0]['*'] = 15;
    dfa[0]['/'] = 15;
    dfa[0]['@'] = 15;
    dfa[0]['&'] = 15;

    // Exp Op (15)
    dfa[0]['^'] = 16;

    // Not Op (16)
    dfa[0]['!'] = 17;

    

    // Rel Op
    dfa[0]['<'] = 18;
    dfa[0]['>'] = 18;
    dfa[16]['='] = 19;
    dfa[17]['='] = 19;

    // dfa[0]['&'] = 18;
    // dfa[0]['|'] = 19;

    // dfa[0][';'] = 20;
    dfa[0]['('] = 19;
    dfa[0][')'] = 20;
    dfa[0]['['] = 21;
    dfa[0][']'] = 22;

    dfa[0]['{'] = 23;
    dfa[0]['}'] = 24;
    dfa[0][','] = 25;
    dfa[0]['.'] = 26;
    dfa[26]['.'] = 27;
    dfa[27]['.'] = 28;
    


    dfaConstructed = 1;
}

TokenType lexGetTokenType(const int state) {
    switch (state) {
        case  0: return TOKEN_ERROR;
        case  1: return TOKEN_ID;
        case  2: return TOKEN_INT_LIT;
        case  3: return TOKEN_ERROR;
        case  4: return TOKEN_REAL_LIT;
        case  5: return TOKEN_INT_LIT;
        case  6: return TOKEN_ERROR;
        case  7: return TOKEN_STRING_LIT;
        case  8: return TOKEN_COLON;
        case  9: return TOKEN_ASSIGN_OP;
        case 10: return TOKEN_ADD_OP;
        case 11: return TOKEN_ADD_OP;
        case 12: return TOKEN_MUL_OP;
        case 13: return TOKEN_EXP_OP;
        case 14: return TOKEN_REL_OP;
        case 15: return TOKEN_REL_OP;
        case 16: return TOKEN_REL_OP;
        case 17: return TOKEN_NOT_OP;
        case 18: return TOKEN_AND_OP;
        case 19: return TOKEN_OR_OP;
        case 20: return TOKEN_SEMICOLON;
        case 21: return TOKEN_LPAREN;
        case 22: return TOKEN_RPAREN;
        case 23: return TOKEN_LBRACK;
        case 24: return TOKEN_RBRACK;
        case 25: return TOKEN_COMMA;
        case 26: return TOKEN_LBRACE;
        case 27: return TOKEN_RBRACE;
        case 28: return TOKEN_ERROR;
        case 29: return TOKEN_ERROR;
        case 30: return TOKEN_ELLIPSE;
        
        default: return TOKEN_EOF;
    }
}

TokenType lexGetTokenKeywordType(const int index) {
    switch (index) {
        case  0: return TOKEN_INT;
        case  1: return TOKEN_REAL;
        case  2: return TOKEN_IF;
        case  3: return TOKEN_ELSE;
        case  4: return TOKEN_FOR;
        case  5: return TOKEN_IN;
        case  6: return TOKEN_WHILE;
        case  7: return TOKEN_PROCEDURE;
        case  8: return TOKEN_ENDIF;
        case  9: return TOKEN_ENDFOR;
        case 10: return TOKEN_ENDWHILE;
        case 11: return TOKEN_ENDPROCEDURE;
        case 12: return TOKEN_CALL;

        default: return TOKEN_ERROR;
    }
}

[[nodiscard]] ullong lexGetToken(Token *tok, const char *is, ullong index) {
    tok->length = 0;
    tok->lineno = lineno;
    tok->type = TOKEN_ERROR;
    tok->value[0] = 0;
    if (!is || !tok)
        return ULLONG_MAX;
    
    // Remove ws
    char ch = is[index];
    while (ch == ' ' || ch == '\t' || ch == '\n') {
        if (ch == '\n') 
            tok->lineno = ++lineno;
        ch = is[++index];
    }

    ch = 0;
    int curr_state = 0;
    int prev_state = -1;
    if (!dfaConstructed)
        init_dfa(dfa);
    while (curr_state != -1) {
        ch = is[index++];
        if (ch == '#') {
            while (ch != '\n') {
                ch = is[index++];
            }
            return lexGetToken(tok, is, index);
        }
        
        tok->value[tok->length++] = ch;
        prev_state = curr_state;
        curr_state = dfa[curr_state][(int)ch];
    }
    --index;
    tok->value[--tok->length] = 0;
    if (*tok->value)
        tok->type = lexGetTokenType(prev_state);
    else
        tok->type = TOKEN_EOF;
        
    if (tok->type == TOKEN_ID) {
        for (int i = 0; i < LEX_TOKEN_NUM_KEYWORDS; i++) {
            bool is_kw = 1;
            int j = 0;
            while (j < tok->length) {
                if (!keywords[i][j] || (keywords[i][j] != tok->value[j])) {
                    is_kw = 0;
                    break;
                }
                j++;
            }
            if (is_kw && !keywords[i][j]) {
                tok->type = lexGetTokenKeywordType(i);
                break;
            }
        }
    }
    return index;
}

void lexPrintToken(Token *tok) {
    if (!tok)
        return;
    
    printf("%s\t->\t%s\n", tok->value, tokenStrings[tok->type]);
}

void lexTokenStreamEnqueue(TokenStream *ts, Token *token) {
    TokenStreamNode *node = (TokenStreamNode *)malloc(sizeof(TokenStreamNode));
    node->next = NULL;
    node->token.length = token->length;
    node->token.type = token->type;
    for (int i = 0; i < LEX_TOKEN_MAX_LENGTH; i++)
        node->token.value[i] = token->value[i];

    if (!ts->back) {
        ts->back = node;
        ts->front = node;
        return;
    }

    ts->back->next = node;
    ts->back = node;
}

void lexTokenStreamDequeue(TokenStream *ts) {
    TokenStreamNode *node = ts->front;
    if (!ts->front->next) {
        free(node);
        ts->front = NULL;
        ts->back = NULL;
        return;
    }

    ts->front = ts->front->next;
    free(node);
}

void lexTokenStreamFront(TokenStream *ts, Token *token) {
    token->length = ts->front->token.length;
    token->type = ts->front->token.type;
    for (int i = 0; i < LEX_TOKEN_MAX_LENGTH; i++)
        token->value[i] = ts->front->token.value[i];
}

bool lexTokenStreamEmpty(TokenStream *ts) {
    return ts->front;
}