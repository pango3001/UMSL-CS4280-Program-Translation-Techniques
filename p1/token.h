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
    BEGIN_TK,
    END_TK,
    LOOP_TK,
    WHOLE_TK,
    VOID_TK,
    EXIT_TK,
    GETTER_TK,
    OUTTER_TK,
    MAIN_TK,
    IF_TK,
    THEN_TK,
    ASSIGN_TK,
    DATA_TK,
    PROC_TK,
    EQUALS_TK,
    EQUALS_OR_LESS_THAN_TK,
    EQUALS_OR_GREATER_THAN_TK,
    EQUALS_EQUALS_TK,
    COLON_TK,
    COLON_EQUALS_TK,
    PLUS_TK,
    MINUS_TK,
    ASTERISK_TK,
    SLASH_TK,
    PERCENT_TK,
    PERIOD_TK,
    LEFT_PAREN_TK,
    RIGHT_PAREN_TK,
    LEFT_BRACKET_TK,
    RIGHT_BRACKET_TK,
    LEFT_BRACE_TK,
    RIGHT_BRACE_TK,
    SEMI_COLON_TK,
    COMMA_TK,
    /* Identifier and Integer Tokens */
    ID_TK,
    INT_TK,
    /* EOF and Error Tokens */
    EOF_TK,
    ERROR_TK
};

/* Token struct */
struct Token
{
    token_id token_identifier;
    std::string token_string;
    unsigned int line_number;

    /* Default Token
     * initializes a Token as an ERROR_TK because if a token is never changed after init
     * then an some kind of error has occured */
    Token()
    {
        this->token_identifier = ERROR_TK;
        this->token_string = "default error token";
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