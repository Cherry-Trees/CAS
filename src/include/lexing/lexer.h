#ifndef LEXER_H
#define LEXER_H

#include "token_stream.h"

void init_dfa(int [256][256]);
token_type_t get_token_type(const int);
token_type_t get_token_keyword_type(const int);
[[nodiscard]] int get_token(token_t *, const char *, int);
void print_token(token_t *);

#endif