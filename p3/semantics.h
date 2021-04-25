#ifndef SEMANTICS_H
#define SEMANTICS_H
#include "token.h"
#include "node.h"

void push(Token tk);
void pop(int scope_begin);
void build_stack();
int topOfStackD(Token tk);
bool var_exists(Token tk);
void print_stack();
void semantic_check(Node* node, int index);
void error_declared(std::string tokenString);


#endif