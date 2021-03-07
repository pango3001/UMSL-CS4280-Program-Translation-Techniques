// Name:    Jesse McCarville-Schueths
// Course:  4280
// Date:    Mar 7, 2021
// Project: P1
// File:    scanner.cpp

#include "scanner.h"
#include "token.h"
#include <string>
#include <map>
#include <fstream>
#include <iostream>

int fsa_table[23][23] = {
    /*   ws   lc    d    =    <    >    :    +    -    *    /    %    .    (    )    ,    {    }    ;    [    ]  eof   uc */
    {     0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16, 17,  18,   19,  20,  -1,  -2},
    {   100,   1,   1, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,   1}, /*ID_TK*/
    {   101, 101,   2, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101}, /*INT_TK*/
    {   102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102}, /*EQUALS_TK*/
    {   103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103}, /*EQUALS_OR_GREATER_THAN_TK*/
    {   104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104}, /*EQUALS_OR_LESS_THAN_TK*/
    {   105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105}, /*EQUALS_OR_EQUALS_TK*/
    {   106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106}, /*COLON_TK*/
    {   107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107}, /*COLON_EQUALS_TK*/
    {   108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108}, /*PLUS_TK*/
    {   109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109}, /*MINUS_TK*/
    {   110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110}, /*ASTERISK_TK*/
    {   111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111}, /*SLASH_TK*/
    {   112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112}, /*PERCENT_TK*/
    {   113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113}, /*PERIOD_TK*/
    {   114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114}, /*LEFT_PAREN_TK*/
    {   115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115}, /*RIGHT_PAREN_TK*/
    {   116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116}, /*COMMA_TK*/
    {   117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117}, /*LEFT_BRACE_TK*/
    {   118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118}, /*RIGHT_BRACE_TK*/
    {   119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119}, /*SEMI_COLON_TK*/
    {   120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120}, /*LEFT_BRACKET_TK*/
    {   121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121}, /*RIGHT_BRACKET_TK*/
};

/* Final State Map
 * maps tokens to corresponding final state number */
std::map<int, token_id> final_states = {
    // Operators and Delimiters
    {102, EQUALS_TK},
    {103, EQUALS_OR_GREATER_THAN_TK},
    {104, EQUALS_OR_LESS_THAN_TK},
    {105, EQUALS_EQUALS_TK},
    {106, COLON_TK},
    {107, COLON_EQUALS_TK},
    {108, PLUS_TK},
    {109, MINUS_TK},
    {110, ASTERISK_TK},
    {111, SLASH_TK},
    {112, PERCENT_TK},
    {113, PERIOD_TK},
    {114, LEFT_PAREN_TK},
    {115, RIGHT_PAREN_TK},
    {116, COMMA_TK},
    {117, LEFT_BRACE_TK},
    {118, RIGHT_BRACE_TK},
    {119, SEMI_COLON_TK},
    {120, LEFT_BRACKET_TK},
    {121, RIGHT_BRACKET_TK},

    /* Identfiers and Integers */
    {100, ID_TK},
    {101, INT_TK},

    /* EOF */
    {-1, EOF_TK} };

/* Keyword Map
 * maps keyword tokens to their corresponding strings */
std::map<std::string, token_id> keywords = {
    {"begin", BEGIN_TK},
    {"end", END_TK},
    {"loop", LOOP_TK},
    {"whole", WHOLE_TK},
    {"void", VOID_TK},
    {"exit", EXIT_TK},
    {"getter", GETTER_TK},
    {"outter", OUTTER_TK},
    {"main", MAIN_TK},
    {"if", IF_TK},
    {"then", THEN_TK},
    {"assign", ASSIGN_TK},
    {"data", DATA_TK},
    {"proc", PROC_TK}
};

/* Character Map
 * maps allowed operators and delimeters to their corresponding column index */
std::map<char, int> allowed_symbols = {
    /* Operators */
    {'=', 2},
    {'<', 3},
    {'>', 4},
    {':', 5},
    {'+', 6},
    {'-', 7},
    {'*', 8},
    {'/', 9},
    {'%', 10},
    {'.', 11},
    /* Delimiters */
    {'(', 12},
    {')', 13},
    {',', 14},
    {'{', 15},
    {'}', 16},
    {';', 17},
    {'[', 18},
    {']', 19}
};

/* Scanner Function */
Token scan(std::ifstream& in_file, unsigned int& line_number)
{
    /* Init current state and next state to start state S0 */
    int current_state = 0;
    int next_state = 0;
    /* Variable to hold the current character being examined */
    char current_char = ' ';
    /* Variable to hold the possible string of characters */
    std::string current_word = "";

    /* Loops until a final state is reached
     * gets the next character on each loop */
    while (current_state < 100 && current_state > -1)
    {
        /* Getting the next available character */
        in_file.get(current_char);

        /* Skipping comments */
        if (current_char == '$')
        {
            /* Keep getting characters until another '$' is reached */
            do
            {
                in_file.get(current_char);
            } while (current_char != '$');
            /* current_char will = '$' so grab next character */
            in_file.get(current_char);
        }
        /* Character determines FSA table column */
        int fsa_column = get_fsa_column(current_char);

        /* If at the end of the file, return EOF token */
        if (in_file.eof())
        {
            fsa_column = 21;
        }
        /* If fsa_column = -2 then the char was invalid
         * return an error Token and display the invalid char to the console */
        if (fsa_column == -2)
        {
            /* Displaying the error message and invalid char */
            std::cout << "SCANNER ERROR: Invalid character \'" << current_char << "\'";
            std::cout << " at line: " << line_number << std::endl;
            /* Returning the error Token */
            return Token(ERROR_TK, "Invalid char", line_number);
        }

        /* Setting the next state */
        next_state = fsa_table[current_state][fsa_column];

        /* If next_state is a final state then return the respective Token */
        if (next_state >= 100 || next_state == -1 || next_state == -2)
        {
            /* EOF state */
            if (next_state == -1)
            {
                return Token(EOF_TK, "EOF", 0);
            }

            if (next_state == -2)
            {
                /* Displaying the error message and invalid char */
                std::cout << "SCANNER ERROR: Invalid character \"" << current_char << "\"";
                std::cout << " at line: " << line_number << std::endl;
                /* Returning the error Token */
                return Token(ERROR_TK, "Invalid ID", line_number);
            }

            /* Other final states */
            in_file.unget();
            return get_token(next_state, current_word, line_number);
        }
        else
        {
            /* If the current char is not a whitespace append to the current word */
            if (!isspace(current_char))
            {
                current_word += current_char;
            }

            if (current_word.length() >= 9)                 // largest indiifier can be 8 chars long
            {
                /* Displaying the error message and invalid char */
                std::cout << "SCANNER ERROR: Invalid length of \"" << current_word << "\"";
                std::cout << " at line: " << line_number << std::endl;
                /* Returning the error Token */
                return Token(ERROR_TK, "Invalid Length", line_number);
            }
            if (current_char == '\n')
            {
                line_number++;
            }

            /* Go to next state */
            current_state = next_state;
        }
    }
    /* If we have not returned a Token yet then the scanner failed */
    return Token(ERROR_TK, "Scanner Faliure", line_number);

}

/* FSA Column Getter */
int get_fsa_column(char current_char)
{
    /* If letter, return column number 1 */
    if (isalpha(current_char))
    {
        if (isupper(current_char))
            return 22;
        return 1;
    }
    /* If digit, return column number 2 */
    else if (isdigit(current_char))
        return 2;
    /* If ws, return column number 0 */
    else if (isspace(current_char))
        return 0;
    /* If EOF, return column column number 21 */
    else if (current_char == EOF)
        return 21;
    /* Else, check if it is an allowed symbol */
    else
    {
        /* If it is an allowed symbol, return respective column number
         * allowed_symbols.find(current_char) returns allowed_symbols.end()
         * if current_char cannot be found in allowed_symbols map */
        if (allowed_symbols.find(current_char) != allowed_symbols.end())
            return allowed_symbols[current_char];
    }
    /* Character is not an allowed character so return -2 to signify error */
    return -2;
}

/* Token Getter */
Token get_token(int state, std::string word, unsigned int line_number)
{
    /* Creating a default token to be returned */
    Token return_token = Token();

    /* Setting Token */
    if (final_states.find(state) != final_states.end())
    {
        return_token.token_identifier = final_states[state];
        return_token.token_string = word;
        return_token.line_number = line_number;
    }
    /* If it is a keyword then modify return token to be the respective keyword token */
    if (keywords.find(word) != keywords.end())
    {
        return_token.token_identifier = keywords[word];
    }

    /* If the return token is not modified for some reason a default error token is still returned*/
    return return_token;
}

