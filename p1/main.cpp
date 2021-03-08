// Name:    Jesse McCarville-Schueths
// Course:  4280
// Date:    Mar 7, 2021
// Project: P1
// File:    main.cpp


#include <iostream>
#include <string>
#include <fstream>
#include "testScanner.h"

int main(int argc, char** argv)
{
    /* Too many arguments */
    if (argc > 2)
    {
        std::cout << "Too many arguments given" << std::endl;
        exit(EXIT_FAILURE);
    }

    /* Filename argument given */
    else if (argc == 2)
    {
        /* Get filename and append extension */
        std::string file_name = argv[1];
        file_name += ".ss21";

        /* Opening the file */
        std::ifstream in_file;
        in_file.open(file_name);

        /* Given filename cannot be opened */
        if (!in_file)
        {
            std::cout << "Error opening " << file_name << " for reading";
            std::cout << std::endl;
            exit(EXIT_FAILURE);
        }

        /* Call the test scanner */
        test_scanner(in_file);
        /* Close the input file */
        in_file.close();

    }

    /* No filename argument given */
    else if (argc == 1)
    {
        std::string userInput;
        std::string fileName;                   // name of file
        std::ifstream inFile;                   // for file input

        /* Creating a temporary file to hold keyboard input */
        std::ofstream tempFile;             // Temp File for keyboard input
        tempFile.open("stdin.temp", std::ios::trunc); // trunc overwrites

        std::string string = "";            // empty string for reading input

        std::cout << "Pressing \"Enter\" on empty line will simulate EOF" << std::endl;

        do {
            std::cout << std::endl << "Keyboard Input: ";
            getline(std::cin, userInput);   // read user input
            tempFile << userInput << " " << std::endl;   // write input to temp file
        } while (!userInput.empty());         // Pressing "Enter" on empty line will sim EOF

        tempFile.close();                   // close file

        std::ifstream in_file;
        in_file.open("stdin.temp");

        /* Cannot open temporary file */
        if (!in_file)
        {
            std::cout << "Error opening " << fileName << " for reading";
            std::cout << std::endl;
            exit(EXIT_FAILURE);
        }

        /* Call the test scanner */
        test_scanner(in_file);
        /* Close the input file */
        in_file.close();
    }
}