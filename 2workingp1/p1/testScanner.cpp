// Name:    Jesse McCarville-Schueths
// Course:  4280
// Date:    Mar 7, 2021
// Project: P1
// File:    testScanner.cpp

#include "testScanner.h"
#include "scanner.h"
#include <iostream>
#include <iomanip>

std::string tokens[] = {"BEGIN_TK","END_TK","LOOP_TK","WHILE_TK", "VOID_TK", "EXIT_TK", "GETTER_TK", "OUTTER_TK", "MAIN_TK", "IF_TK", "THEN_TK", "ASSIGN_TK", "DATA_TK", "PROC_TK", "EQUALS_TK", "EQUALS_OR_LESS_THAN_TK", "EQUALS_OR_GREAT_THAN_TK", "EQUALS_EQUALS_TK", "COLON_TK", "COLON_EQUALS_TK", "PLUS_TK", "MINUS_TK", "ASTERISK_TK", "SLASH_TK", "PERCENT_TK", "PERIOD_TK", "LEFT_PAREN_TK", "RIGHT_PAREN_TK", "COMMA_TK", "LEFT_BRACE_TK", "RIGHT_BRACE_TK", "SEMI_COLON_TK", "LEFT_BRACKET_TK", "RIGHT_BRACKET_TK", "ID_TK", "INT_TK", "EOF_TK", "ERROR_TK"};

void test_scanner(std::ifstream& input)
{
    /* Temporary blank/default token */
    Token current_token = Token();
    /* File line number */
    unsigned int line_number = 1;
    do
    {
        Token current_token = scan(input, line_number);
        if (current_token.token_identifier == ERROR_TK)
        {
            exit(EXIT_FAILURE);
        }
        else
        {
            print_token(current_token);
        }

    } while (input);

    return;
}

void print_token(Token token)
{
    std::cout << std::left;
    std::cout << "Line: " << std::setw(3) << token.line_number;
    std::cout << "\tType: " << std::setw(22) << tokens[token.token_identifier];
    std::cout << "\tToken: " << std::setw(10) << token.token_string << std::endl;
    return;
}