#include <iostream>
#include <string>

using namespace std;

#include "src/include/lexing/lexer.h"

int main() {

    const char *prog = "x = $\"x\";\nf = $\"f\": x -> x^2 + 1;";

    token_t token;
    token.type = TOKEN_ERROR;
    token.length = 0;
    
    int idx = 0;
    cout << "Input Program:" << endl << prog << endl << endl;
    while (token.type != TOKEN_EOF) {
        idx = get_token(&token, prog, idx);
        print_token(&token);
    }

    return 0;
}