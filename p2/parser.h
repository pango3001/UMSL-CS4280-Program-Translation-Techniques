#ifndef PARSER_H
#define PARSER_H
#include "token.h"
#include "node.h"

extern std::ifstream in_file;

Node* parser();

Node* program();
Node* block(unsigned int depth);
Node* vars(unsigned int depth);
Node* expr(unsigned int depth);
Node* n(unsigned int depth);
Node* a(unsigned int depth);
Node* m(unsigned int depth);
Node* r(unsigned int depth);
Node* stats(unsigned int depth);
Node* mstat(unsigned int depth);
Node* stat(unsigned int depth);
Node* in(unsigned int depth);
Node* out(unsigned int depth);
Node* iff(unsigned int depth);
Node* loop(unsigned int depth);
Node* assign(unsigned int depth);
Node* ro(unsigned int depth);
Node* gotoo(unsigned int depth);
Node* label(unsigned int depth);

void error(tokens expected, Token recieved);
void error(tokens expected1, tokens expected2, Token recieved);
void error(tokens expected1, tokens expected2, tokens expected3, Token recieved);
void error_stat(Token recieved);

bool is_stat(tokens tk);
bool is_ro(tokens tk);

void print_tree(Node* node);

#endif