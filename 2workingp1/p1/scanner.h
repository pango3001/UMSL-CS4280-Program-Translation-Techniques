// Name:    Jesse McCarville-Schueths
// Course:  4280
// Date:    Mar 7, 2021
// Project: P1
// File:    scanner.h

#ifndef SCANNER_H
#define SCANNER_H
#include "token.h"
#include <string>
#include <map>
#include <fstream>

/* Scanner Function */
Token scan(std::ifstream& in_file, int& line_number);

/* FSA Column Getter */
int get_fsa_column(char current_char);

/* Token Getter */
Token get_token(int state, std::string word, int line_number);

#endif