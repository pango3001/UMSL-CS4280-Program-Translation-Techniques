// Name:    Jesse McCarville-Schueths
// Course:  4280
// Date:    Mar 7, 2021
// Project: P1
// File:    token.h

#ifndef TOKEN_H
#define TOKEN_H

#include <string>

/* Enum to represent each token */
enum token_id
{
    /* Keyword Tokens */
    BEGIN_TK,                 // 0
    END_TK,                   // 1
    LOOP_TK,                  // 2
    WHOLE_TK,                 // 3
    VOID_TK,                  // 4
    EXIT_TK,                  // 5
    GETTER_TK,                // 6
    OUTTER_TK,                // 7
    MAIN_TK,                  // 8
    IF_TK,                    // 9
    THEN_TK,                  // 10
    ASSIGN_TK,                // 11
    DATA_TK,                  // 12
    PROC_TK,                  // 13
    EQUALS_TK,                // 14
    EQUALS_OR_LESS_THAN_TK,   // 15
    EQUALS_OR_GREAT_THAN_TK,  // 16
    EQUALS_EQUALS_TK,         // 17
    COLON_TK,                 // 18
    COLON_EQUALS_TK,          // 19
    PLUS_TK,                  // 20
    MINUS_TK,                 // 21
    ASTERISK_TK,              // 22
    SLASH_TK,                 // 23
    PERCENT_TK,               // 24
    PERIOD_TK,                // 25
    LEFT_PAREN_TK,            // 26
    RIGHT_PAREN_TK,           // 27
    COMMA_TK,                 // 28
    LEFT_BRACE_TK,            // 29
    RIGHT_BRACE_TK,           // 30
    SEMI_COLON_TK,            // 31
    LEFT_BRACKET_TK,          // 32
    RIGHT_BRACKET_TK,         // 33
    ID_TK,                    // 34
    INT_TK,                   // 35
    EOF_TK,                   // 36
    ERROR_TK                  // 37
};


class Token
{
    token_id token_identifier;
    std::string token_string;
    unsigned int line_number;

    Token()
    {
        this->token_identifier = ERROR_TK;
        this->token_string = "default token";
        this->line_number = 0;
    }

    /* Standard Token */
    Token(token_id token_identifier, std::string token_string, unsigned int line_number)
    {
        this->token_identifier = token_identifier;
        this->token_string = token_string;
        this->line_number = line_number;
    }
};

#endif