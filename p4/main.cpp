// Name:    Jesse McCarville-Schueths
// Course:  4280
// Date:    April 11, 2021
// Project: P4
// File:    main.cpp


#include <iostream>
#include <string>
#include <fstream>
#include "parser.h"
#include "semantics.h"



std::ofstream file;


int main(int argc, char** argv) {
    std::string file_name;         // filename
    std::string file_n;         // filename
    
    static std::string out_file_name;
    
    // FILE GIVEN
    if (argc == 2) {
        file_name = argv[1];
        file_n = argv[1];
        file_name += ".ss21";

        out_file_name = file_n + ".asm";

        std::ofstream outfile;
        outfile.open(file_name, std::ios_base::app);
        outfile << " ";
        in_file.open(file_name);

    }

    // USER INPUT
    else if (argc == 1) {
        std::string userInput;
        std::ofstream tempFile;                 // TempFile for user input
        file_name = "stdin.temp";

        tempFile.open(file_name, std::ios::trunc); // trunc overwrites

        std::string string = "";                // empty string for reading input

        std::cout << "Pressing \"Enter\" on empty line will simulate EOF" << std::endl;

        do {
            std::cout << std::endl << "Keyboard Input: ";
            getline(std::cin, userInput);   // read user input
            tempFile << userInput << "\n";   // write input to temp file
        } while (!userInput.empty());         // Pressing "Enter" on empty line will sim EOF

        tempFile.close();                   // close file
        in_file.open(file_name);
        out_file_name = "kb.asm";
    }

    //more than 1 argument quits
    else {
        std::cout << "Too many arguments given" << std::endl;
        exit(EXIT_FAILURE);
    }

    

    // Scan and parse file
    if (in_file) {
        
        
        //std::cout << "Starting the parser..." << std::endl;
        Node* root = parser(); // run parser
        //print_tree(root);      // print tree
        //semantic_check(root, 0);  //checks semantics
        codeGen(root, 0, out_file_name);  //checks semantics
        in_file.close(); // close file

        std::cout << "Successfully created: " << out_file_name << std::endl;

    }
    else {  // cannot open file
        std::cout << "ERROR: Cannot open " << file_name << " for reading" << std::endl;
        in_file.close();
        exit(EXIT_FAILURE);
    }
    return 0;
}