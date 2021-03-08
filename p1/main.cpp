// Name:    Jesse McCarville-Schueths
// Course:  4280
// Date:    Mar 7, 2021
// Project: P1
// File:    main.cpp


#include <iostream>
#include <string>
#include <fstream>
#include "testScanner.h"

int main(int argc, char** argv) {
    std::ifstream inFile;
    std::string fileName;

    // FILE GIVEN
    if (argc == 2) {
        fileName = argv[1];
        fileName += ".ss21";
        inFile.open(fileName);
    }

    // USER INPUT
    else if (argc == 1) {
        std::string userInput;
        std::ofstream tempFile;                 // TempFile for user input

        tempFile.open("stdin.temp", std::ios::trunc); // trunc overwrites

        std::string string = "";                // empty string for reading input

        std::cout << "Pressing \"Enter\" on empty line will simulate EOF" << std::endl;

        do {
            std::cout << std::endl << "Keyboard Input: ";
            getline(std::cin, userInput);   // read user input
            tempFile << userInput << "\n";   // write input to temp file
        } while (!userInput.empty());         // Pressing "Enter" on empty line will sim EOF

        tempFile.close();                   // close file

        std::ifstream inFile;
        inFile.open("stdin.temp");
    }

    else {
        std::cout << "Too many arguments given" << std::endl;
        exit(EXIT_FAILURE);
    }

    inFile.open(fileName);

    /* Cannot open temporary file */
    if (!inFile) {
        std::cout << "Error opening " << fileName << " for reading";
        std::cout << std::endl;
        exit(EXIT_FAILURE);
    }

    /* Call the test scanner */
    testScanner(inFile);
    /* Close the input file */
    inFile.close();


}