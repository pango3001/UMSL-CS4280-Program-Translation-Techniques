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

int fsa_table[23][23] = {   // [row] [col]   ws = whitespace, lc = lowercase, UC = UpperCase, dig = digit, eof = end of file
 //   ws   lc   UC  dig    =    <    >    :    +    -    *    /    %    .    (    )    ,    {    }    ;    [    ]  eof  
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

// Map for Keywords
std::map<std::string, tokens> keywords = {
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

// Map for symbols
std::map<char, int> symbols = {
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

// Map for Operators and Delimiters
std::map<int, tokens> endState = {
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
};



// scanner for token
Token scanner(std::ifstream& in_file, unsigned int& lineNum){
    int state = 0;             
    int lookAhead = 0;
   
    char current_char = ' ';       
    
    std::string current_word = "";   
    
    while (state < 100){
        in_file.get(current_char);
        
        // Skips comments 
        if (current_char == '$'){
            in_file.get(current_char);
            if (current_char == '$') {
                in_file.get(current_char);
                while (1) {   // loop until break
                    in_file.get(current_char);
                    if (in_file.eof()) {
                        std::cout << "SCANNER ERROR: Comment not closed, EOF reached at line: " << lineNum << std::endl;   // in case comment is never closed
                        return Token(ERROR_TK, "No end to comment", lineNum);
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
        
        int colFSA = setFSAcol(current_char);
        
        if (in_file.eof()){
            colFSA = 22;
        }

        if (colFSA == 23)
        {

            std::cout << "SCANNER ERROR: Invalid character \'" << current_char << "\'";
            std::cout << " at line: " << lineNum << std::endl;

            return Token(ERROR_TK, "Invalid char", lineNum);
        }

        lookAhead = fsa_table[state][colFSA];

        if (lookAhead == 23) {
            std::cout << "SCANNER ERROR 2: Invalid character \"" << current_char << "\"";
            std::cout << " at line: " << lineNum << std::endl;
            return Token(ERROR_TK, "Invalid ID", lineNum);
        }

        else if (lookAhead == -1) {
            return Token(EOF_TK, "EOF", lineNum);
        }
        
        else if (lookAhead >= 100)
        {
            in_file.unget();
            return get_token(lookAhead, current_word, lineNum);
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
                std::cout << " at line: " << lineNum << std::endl;
                return Token(ERROR_TK, "Invalid Length", lineNum);
            }
            if (current_char == '\n')
            {
                lineNum++;
            }
 
            state = lookAhead;
        }
    }

    return Token(ERROR_TK, "Scanner Failed", lineNum);

}

int setFSAcol(char current_char){
    
    if (current_char == EOF)
        return 22;

    if (isspace(current_char))
        return 0;       // ws
    
    if (isalpha(current_char) || current_char == '_'){
        if (isupper(current_char))
            return 2;   // UC
        return 1;       // lc
    }

    if (isdigit(current_char))
        return 3;       // dig


    else  // valid symbol
    {
        if (symbols.find(current_char) != symbols.end())
            return symbols[current_char];
    }

    return 23;  // Leads to error state
}


Token setToken(int state, std::string word, unsigned int lineNum){

    if (keywords.find(word) != keywords.end()) {
         return Token(keywords[word], word, lineNum);
    }
    
    else {
        return Token(endState[state], word, lineNum);
    }
}

