// Name:    Jesse McCarville-Schueths
// Course:  4280
// Date:    Mar 7, 2021
// Project: P1
// File:    testScanner.h

#ifndef TESTSCANNER_H
#define TESTSCANNER_H

#include <fstream>
#include "token.h"

void testScanner(std::ifstream& file);
void printTokenInfo(Token token);

#endif