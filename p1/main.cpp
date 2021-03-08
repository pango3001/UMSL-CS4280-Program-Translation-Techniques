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
    std::ifstream inFile;         // input file
    std::string fileName;         // filename

    // FILE GIVEN
    if (argc == 2) {
        fileName = argv[1];
        fileName += ".fs";
        
        std::ofstream outfile;
        outfile.open(fileName, std::ios_base::app);
        outfile << " ";
        std::cout << "stdin.temp" << std::endl;

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
        std::cout << "stdin.temp" << std::endl;
    }

    //more than 1 argument quits
    else {
        std::cout << "Too many arguments given" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Scan file
    if (inFile) {

        testScanner(inFile);  //scan file with testScanner

        inFile.close(); // close file

    }
    else {  // cannot open file
    std::cout << "ERROR: Cannot open " << fileName << " for reading" << std::endl;

    exit(EXIT_FAILURE);
    }
    return 0;
}