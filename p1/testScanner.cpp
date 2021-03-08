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

void testScanner(std::ifstream& file) {

    unsigned int lineNum = 1;
    do
    {
        // Scan in tokens from file
        Token current_token = scan(file, lineNum);
        if (current_token.token_ID == ERROR_TK) {
            exit(EXIT_FAILURE);
        }
        else {  // print token info to screen
            printTokenInfo(current_token);
        }

    } while (file);
}

void printTokenInfo(Token token){
    std::cout << std::left;
    std::cout << "Line: " << std::setw(3) << token.lineNum;
    std::cout << "\tType: " << std::setw(22) << tokens[token.token_ID];
    std::cout << "\tToken: " << std::setw(10) << token.token_string << std::endl;
}