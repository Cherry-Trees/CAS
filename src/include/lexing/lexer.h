#ifndef LEXER_H
#define LEXER_H

#include "token_stream.h"

// void dfa_set(DFA *dfa, const int value, const int row, const int col);
// int dfa_get(DFA *dfa, const int row, const int col);




void init_dfa(int dfa[256][256]);
token_type_t get_token_type(const int state);
token_type_t get_token_keyword_type(const int index);
[[nodiscard]] int get_token(token_t *token, const char *is, int index);
void print_token(token_t *token);





#endif