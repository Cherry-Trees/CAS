#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H

#include "../global/global.h"
#include "token.h"

typedef struct token_stream_node token_stream_node_t;
typedef struct token_stream token_stream_t;

struct token_stream_node {
    token_t token;
    token_stream_node_t *next;
};

struct token_stream {
    token_stream_node_t *front;
    token_stream_node_t *back;
};

void token_stream_enqueue(token_stream_t *, token_t *);
void token_stream_dequeue(token_stream_t *);
void token_stream_front(token_stream_t *, token_t *);
bool token_stream_empty(token_stream_t *);

#endif