// Name:    Jesse McCarville-Schueths
// Course:  4280
// Date:    Feb 7, 2021
// Project: P0
// File:    main.cpp

#include <iostream>
#include <string>
#include <fstream>
#include "tree.h"
#include "node.h"


void printInorder(std::string);
void printPreorder(std::string);
void printPostorder(std::string);
// buildTree() can be found in tree.cpp

int main(int argc, char** argv) {
    if (argc > 2){                          // If more than 1 argument
        std::cout << "Error: Too many arguments" << std::endl;
        return 0;
    }

    std::string userInput;
    std::string fileName;                   // name of file
    std::ifstream inFile;                   // for file input

    if (argc == 1) {                        // No argument: Keyboard input
        std::ofstream tempFile;             // Temp File for keyboard input
        tempFile.open("file.temp", std::ios::trunc); // trunc overwrites

        std::string string = "";            // empty string for reading input

        do {
            std::cout << std::endl << ">>: ";
            getline(std::cin, userInput);
            tempFile << userInput << " ";
        }
        while (!userInput.empty());
        
        /*
        while (std::cin >> string)          // Read in entire file
            tempFile << (string + ' ');
*/
        tempFile.close();                   // close file

        inFile.open("file.temp", std::ios::in); // keyboard input inputted into temp.file

        fileName = "p0_output";              // output file for tree
    }


    if (argc == 2) {
        fileName = argv[1];
        inFile.open(fileName + ".sp2020");   // output file for tree
    }

    if (inFile) {
        Tree binaryTree;                     // create tree 
        
        binaryTree.root = binaryTree.buildTree(inFile);         // fill tree
        binaryTree.traversePreorder(binaryTree.root, fileName); // create output file for preorder traversal
        binaryTree.traverseInorder(binaryTree.root, fileName);  // create output file for inorder traversal
        binaryTree.traversePostorder(binaryTree.root, fileName);// create output file for postorder traversal
        

        inFile.close();                         // close file

        printInorder(fileName);                 // print inorder traversal to screen
        printPreorder(fileName);                // print preorder traversal to screen
        printPostorder(fileName);               // print postorder traversal to screen
    }

    else { // can't read/find file
        std::cout << "Error: File not found." << std::endl;
        return 0;
    }

    return 0;
}

// Function: print inorder traversal to screen 
void printInorder(std::string fileName) {
    std::cout << "Inorder traversal:" << std::endl;
    std::ifstream f(fileName + ".inorder");

    if (f.is_open())
        std::cout << f.rdbuf();     // print entire file
    std::cout << "\n";
}

// Function: print preorder traversal to screen
void printPreorder(std::string fileName) {
    std::cout << "Preorder traversal:" << std::endl;
    std::ifstream f(fileName + ".preorder");

    if (f.is_open())
        std::cout << f.rdbuf();     // print entire file
    std::cout << "\n";
}

// Function: print postorder traversal to screen
void printPostorder(std::string fileName) {
    std::cout << "Postorder traversal:" << std::endl;
    std::ifstream f(fileName + ".postorder");

    if (f.is_open())  
        std::cout << f.rdbuf();     // print entire file
    std::cout << "\n";
}