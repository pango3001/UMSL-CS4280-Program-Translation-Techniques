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

int fsa_table[23][23] = {   // [row] [col]
 /*   ws   lc   UC  dig    =    <    >    :    +    -    *    /    %    .    (    )    ,    {    }    ;    [    ]  eof  */
    {  0,   1,  23,   2,   3,   4,   5,   7,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  -1}, // 0
    {100,   1,   1, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100}, // 1 id
    {101, 101, 101,   2, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101}, // 2 int
    {102, 102, 102, 102,   6,   5,   4, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102}, // 3 =
    {103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103}, // 4 =>
    {104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104}, // 5 =<
    {105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105}, // 6 ==
    {106, 106, 106, 106,   8, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106}, // 7 :
    {107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107}, // 8 :=
    {108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108}, // 9 +
    {109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109}, // 10 -
    {110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110}, // 11 *
    {111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111}, // 12 /
    {112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112}, // 13 %
    {113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113}, // 14 .
    {114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114}, // 15 (
    {115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115}, // 16 )
    {116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116}, // 17 ,
    {117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117}, // 18 {
    {118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118}, // 19 }
    {119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119}, // 20 ;
    {120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120}, // 21 [
    {121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121}  // 22 ]
};

std::map<int, token_id> final_states = {
    // Operators and Delimiters
    {100, ID_TK},
    {101, INT_TK},
    {-1, EOF_TK},
    {102, EQUALS_TK},
    {103, EQUALS_OR_GREAT_THAN_TK},
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
    {121, RIGHT_BRACKET_TK}
}
;

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
    {'=', 4},
    {'<', 5},
    {'>', 6},
    {':', 7},
    {'+', 8},
    {'-', 9},
    {'*', 10},
    {'/', 11},
    {'%', 12},
    {'.', 13},
    {'(', 14},
    {')', 15},
    {',', 16},
    {'{', 17},
    {'}', 18},
    {';', 19},
    {'[', 20},
    {']', 21}
};

/* Scanner Function */
Token scan(std::ifstream& in_file, unsigned int& line_number){
    int current_state = 0;             
    int next_state = 0;
   
    char current_char = ' ';       
    
    std::string current_word = "";   
    
    while (current_state < 100 && current_state > -1){
        
        in_file.get(current_char);

        /* Skipping comments */
        if (current_char == '$'){
            in_file.get(current_char);
            if (current_char == '$') {
                in_file.get(current_char);
                while (1) {   // loop until break
                    in_file.get(current_char);
                    if (in_file.eof()) {
                        std::cout << "SCANNER ERROR: Comment not closed, EOF reached at line: " << line_number << std::endl;
                        return Token(ERROR_TK, "No end to comment", line_number);
                    }
                    if (current_char == '$') {
                        in_file.get(current_char);  
                        if (current_char == '$') {
                            in_file.get(current_char);
                            break;
                        }
                    }
                }
            }        
        }
        
        int fsa_column = get_fsa_column(current_char);
        //std::cout << "Test Point 1" << current_char << std::endl;
        
        if (in_file.eof()){
            fsa_column = 22;
        }

        if (fsa_column == 23)
        {

            std::cout << "SCANNER ERROR 1: Invalid character \'" << current_char << "\'";
            std::cout << " at line: " << line_number << std::endl;

            return Token(ERROR_TK, "Invalid char", line_number);
        }

        next_state = fsa_table[current_state][fsa_column];
        //std::cout << "Test Point 2" << current_char << std::endl;

        if (next_state == 23) {
            std::cout << "SCANNER ERROR 2: Invalid character \"" << current_char << "\"";
            std::cout << " at line: " << line_number << std::endl;
            return Token(ERROR_TK, "Invalid ID", line_number);
        }

        else if (next_state == -1) {
            return Token(EOF_TK, "EOF", line_number);
        }
        
        else if (next_state >= 100)
        {
            in_file.unget();
            //std::cout << " current state: " << current_state << " next state: " << next_state << " current_word: " << current_word << std::endl;
            return get_token(next_state, current_word, line_number);
        }
        else
        {

            if (!isspace(current_char))
            {
                current_word += current_char;
            }

            if (current_word.length() >= 9)                 // largest indiifier can be 8 chars long
            {
                std::cout << "SCANNER ERROR 3: Invalid length of \"" << current_word << "\"";
                std::cout << " at line: " << line_number << std::endl;
                return Token(ERROR_TK, "Invalid Length", line_number);
            }
            if (current_char == '\n')
            {
                line_number++;
            }

            current_state = next_state;
        }
    }

    return Token(ERROR_TK, "Scanner Faliure", line_number);

}

int get_fsa_column(char current_char){
    
    if (isspace(current_char))
        return 0;       // ws
    
    if (isalpha(current_char)){
        if (isupper(current_char))
            return 2;   // UC
        return 1;       // lc
    }

    if (isdigit(current_char))
        return 3;       // dig

    if (current_char == EOF)
        return 22;

    else  // valid symbol
    {
        if (allowed_symbols.find(current_char) != allowed_symbols.end())
            //std::cout << " Char: " << allowed_symbols[current_char] << std::endl;
            return allowed_symbols[current_char];
    }

    return 23;  // Leads to error state
}

/* Token Getter */
Token get_token(int state, std::string word, unsigned int line_number)
{
    /* Creating a default token to be returned */
    //Token return_token = Token();

    /* Setting Token */
    if (final_states.find(state) != final_states.end())
    {
        return Token(final_states[state], word, line_number);
        //return_token.token_identifier = final_states[state];
        //return_token.token_string = word;
       // return_token.line_number = line_number;
    }
    /* If it is a keyword then modify return token to be the respective keyword token */
    if (keywords.find(word) != keywords.end())
    {
        std::cout << " Char: " << keywords[word] << std::endl;
        
        return Token(keywords[word], word, line_number);
        //return_token.token_identifier = keywords[word];
    }

    /* If the return token is not modified for some reason a default error token is still returned*/
    //return return_token;
}

