///* Includes */
//#include <iostream>
//#include <string>
//#include <fstream>
//#include "parser.h"
//
//int main(int argc, char** argv)
//{
//    /* Too many arguments */
//    if (argc > 2)
//    {
//        std::cout << "Too many arguments given" << std::endl;
//        exit(EXIT_FAILURE);
//    }
//
//    /* Filename argument given */
//    else if (argc == 2)
//    {
//        /* Get filenaema and append extension */
//        std::string file_name = argv[1];
//        file_name += ".fs18";
//
//        std::ofstream outfile;
//        outfile.open(file_name, std::ios_base::app);
//        outfile << " ";
//        
//        /* Opening the file */
//        // std::ifstream in_file;
//        in_file.open(file_name);
//
//        /* Given filename cannot be opened */
//        if (!in_file)
//        {
//            std::cout << "Error opening " << file_name << " for reading";
//            std::cout << std::endl;
//            exit(EXIT_FAILURE);
//        }
//
//        /* Call the parser */
//        Node* root = parser();
//        print_tree(root);        
//        /* Close the input file */
//        in_file.close();
//
//    }
//
//    /* No filename argument given */
//    else if (argc == 1)
//    {
//        /* Creating a temporary file to hold keyboard input */ 
//        std::ofstream temp_file;
//        std::string file_name = "keyboard_input.txt";
//        temp_file.open(file_name, std::ios::trunc);
//
//        /* Cannot open temporary file */
//        if (!temp_file)
//        {
//            std::cout << "Error opening " << file_name << " for writing";
//            std::cout << std::endl;
//            exit(EXIT_FAILURE);
//        }
//
//        /* Helper string variable */
//        char current_char;
//
//        /* Writing keyboard input to temporary file */
//        while (std::cin >> std::noskipws >> current_char)
//            temp_file << current_char;
//    
//        /* Closing the file */
//        temp_file.close();        
//        
//        /* Opening keyboard input */
//        in_file.open(file_name);
//
//        /* Cannot open temporary file */
//        if (!in_file)
//        {
//            std::cout << "Error opening " << file_name << " for reading";
//            std::cout << std::endl;
//            exit(EXIT_FAILURE);
//        }
//        /* TODO */
//        /* Call the parser */
//        parser();
//        /* Close the input file */
//        in_file.close();
//    }
//}



// Name:    Jesse McCarville-Schueths
// Course:  4280
// Date:    Mar 7, 2021
// Project: P1
// File:    main.cpp


#include <iostream>
#include <string>
#include <fstream>
#include "parser.h"

int main(int argc, char** argv) {
    std::ifstream inFile;         // input file
    std::string fileName;         // filename

    // FILE GIVEN
    if (argc == 2) {
        fileName = argv[1];
        fileName += ".fs18";

        std::ofstream outfile;
        outfile.open(fileName, std::ios_base::app);
        outfile << " ";
        outfile.close();

    }

    // USER INPUT
    else if (argc == 1) {
        std::string userInput;
        std::ofstream tempFile;                 // TempFile for user input
        fileName = "stdin.temp";

        tempFile.open(fileName, std::ios::trunc); // trunc overwrites

        std::string string = "";                // empty string for reading input

        std::cout << "Pressing \"Enter\" on empty line will simulate EOF" << std::endl;

        do {
            std::cout << std::endl << "Keyboard Input: ";
            getline(std::cin, userInput);   // read user input
            tempFile << userInput << "\n";   // write input to temp file
        } while (!userInput.empty());         // Pressing "Enter" on empty line will sim EOF

        tempFile.close();                   // close file

    }

    //more than 1 argument quits
    else {
        std::cout << "Too many arguments given" << std::endl;
        exit(EXIT_FAILURE);
    }

    inFile.open(fileName);

    // Scan file
    if (inFile) {
        /* Call the parser */
        Node* root = parser();
        print_tree(root);        
        /* Close the input file */
        in_file.close();

    }
    else {  // cannot open file
        std::cout << "ERROR: Cannot open " << fileName << " for reading" << std::endl;

        exit(EXIT_FAILURE);
    }
    return 0;
}