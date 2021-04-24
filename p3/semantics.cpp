#include "semantics.h"
#include <iostream>
#include <iomanip>

/* assume no more than 100 items in a program and generate stack overflow if more */
const int max_stack_size = 100;

Token stack[max_stack_size];

int var_count = 0;
int scope_begin = 0;

bool debug1 = true;

void build_stack()
{
    for (int i = 0; i <= max_stack_size; i++)
        stack[i].token_string = "";
}

void push(Token tk)
{
    if (var_count >= max_stack_size)
    {
        std::cout << "ERROR: Full stack" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        for (int i = scope_begin; i < var_count; i++)
        {
            if (stack[i].token_string == tk.token_string)
            {
                std::cout << "ERROR: " << tk.token_string << " has already been declared in this scope" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        var_count++; if (debug1) { std::cout << "VAR COUNT: " << var_count << "\n"; }  // for debugging
        stack[var_count] = tk; if (debug1) { std::cout << "Adding \'" << tk.token_string << "\' to the stack\n"; }  // for debugging 
       
    }
}

void pop(int scope_begin)
{
    for (int i = var_count; i > scope_begin; i--)
    {
        var_count--;
        stack[i].token_string == "";
    }
}

int find(Token tk)
{
    for (int i = var_count; i >= scope_begin; i--)
    {
        //std::cout << scope_begin << " " << var_count << std::endl;
        if (stack[i].token_string == tk.token_string)
        {
            int tos_distance = var_count - 1 - i;
            return tos_distance;
        }
    }

    return -1;
}

bool var_exists(Token tk)
{
    for (int i = var_count - 1; i > -1; i--)
    {
        if (stack[i].token_string == tk.token_string)
            return true;
    }

    return false;
}

void semantic_check(Node* node, int count)
{
    if (node == nullptr)
        return;
    if (debug1) {
        if (node->name == "<vars>") { std::cout << "Working on: " << std::setw(10) << std::left << node->name << "| Token: " << std::setw(9) << std::left << node->token_2.token_string << "| " << print_stack(); }  // for debugging
        else { std::cout << "Working on: " << std::setw(10) << std::left << node->name << "| Token: " << std::setw(9) << std::left << node->token_1.token_string << "| " << print_stack(); }  // for debugging
    }
    if (node->name == "<program>")
    {
        unsigned int num_vars = 0;
        if (node->child_1 != nullptr)
            semantic_check(node->child_1, num_vars);
        if (node->child_2 != nullptr)
            semantic_check(node->child_2, num_vars);
        if (node->child_3 != nullptr)
            semantic_check(node->child_3, num_vars);
        if (node->child_4 != nullptr)
            semantic_check(node->child_4, num_vars);
    }
    else if (node->name == "<vars>")
    {
        int tos_distance = find(node->token_2);
        scope_begin = var_count;

        if (tos_distance == -1 || tos_distance > count)
        {
            
            push(node->token_2);
            count++;
        }
        else if (tos_distance < count)
        {
            std::cout << "ERROR: " << node->token_2.token_string << " has already been defined in this scope" << std::endl;
            exit(EXIT_FAILURE);
        }

        if (node->child_1 != nullptr)
            semantic_check(node->child_1, count);
    }
    else if (node->name == "<block>")
    {
        unsigned int num_vars = 0;
        scope_begin = var_count;

        if (node->child_1 != nullptr)
            semantic_check(node->child_1, num_vars);
        if (node->child_2 != nullptr)
            semantic_check(node->child_2, num_vars);
        if (node->child_3 != nullptr)
            semantic_check(node->child_3, num_vars);
        if (node->child_4 != nullptr)
            semantic_check(node->child_4, num_vars);

        pop(scope_begin);
    }
    else if (node->name == "<expr>")
    {
        if (node->token_1.token_ID == MINUS_TK)
        {
            if (node->child_1 != nullptr)
                semantic_check(node->child_1, count);
            if (node->child_2 != nullptr)
                semantic_check(node->child_2, count);
            if (node->child_3 != nullptr)
                semantic_check(node->child_3, count);
            if (node->child_4 != nullptr)
                semantic_check(node->child_4, count);
        }
        else if (node->child_1 != nullptr)
            semantic_check(node->child_1, count);
    }
    else if (node->name == "<N>")
    {
        if (node->token_1.token_ID == SLASH_TK || node->token_1.token_ID == ASTERISK_TK)
        {
            if (node->child_1 != nullptr)
                semantic_check(node->child_1, count);
            if (node->child_2 != nullptr)
                semantic_check(node->child_2, count);
            if (node->child_3 != nullptr)
                semantic_check(node->child_3, count);
            if (node->child_4 != nullptr)
                semantic_check(node->child_4, count);
        }
        else if (node->child_1 != nullptr)
            semantic_check(node->child_1, count);
    }
    else if (node->name == "<M>")
    {
        if (node->token_1.token_ID == ASTERISK_TK)
        {
            if (node->child_1 != nullptr)
                semantic_check(node->child_1, count);
            if (node->child_2 != nullptr)
                semantic_check(node->child_2, count);
            if (node->child_3 != nullptr)
                semantic_check(node->child_3, count);
            if (node->child_4 != nullptr)
                semantic_check(node->child_4, count);
        }
        else if (node->child_1 != nullptr)
            semantic_check(node->child_1, count);
    }



    else if (node->name == "<A>")
    {
        if (node->token_1.token_ID == PLUS_TK)
        {
            if (node->child_1 != nullptr)
                semantic_check(node->child_1, count);
            if (node->child_2 != nullptr)
                semantic_check(node->child_2, count);
            if (node->child_3 != nullptr)
                semantic_check(node->child_3, count);
            if (node->child_4 != nullptr)
                semantic_check(node->child_4, count);
        }
        else if (node->child_1 != nullptr)
            semantic_check(node->child_1, count);
    }

    else if (node->name == "<R>")
    {
        if (node->token_1.token_ID == ID_TK || node->token_1.token_ID == INT_TK)
        {
            if (!var_exists(node->token_2))
            {
                std::cout << "ERROR: " << node->token_2.token_string << " has not been declared in this scope" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else if (node->child_1 != nullptr)
            semantic_check(node->child_1, count);
    }
    else if (node->name == "<in>")
    {
        if (!var_exists(node->token_2))
        {
            std::cout << "ERROR: " << node->token_2.token_string << " has not been declared in this scope" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else if (node->name == "<assign>")
    {
        if (!var_exists(node->token_2))
        {
            std::cout << "ERROR: " << node->token_2.token_string << " has not been declared in this scope" << std::endl;
            exit(EXIT_FAILURE);
        }
        if (node->child_1 != nullptr)
            semantic_check(node->child_1, count);
    }
    else
    {
        if (node->child_1 != nullptr)
            semantic_check(node->child_1, count);
        if (node->child_2 != nullptr)
            semantic_check(node->child_2, count);
        if (node->child_3 != nullptr)
            semantic_check(node->child_3, count);
        if (node->child_4 != nullptr)
            semantic_check(node->child_4, count);
    }
}

//void print_stack() {
//    std::cout << "Stack: ";
//    for (auto i = 0; i < max_stack_size; i++) {
//        if (stack[i].token_string == "")break;
//        std::cout << stack[i].token_string << "";
//    }
//    std::cout << std::endl;
//}

void print_stack() {
    std::cout << "Stack: ";
    int i;
    for (i = 0; i < max_stack_size; i++) {
        std::cout << stack[i].token_string << "";
        if (stack[i].token_string == "")break;
    }
    std::cout << std::endl;
}