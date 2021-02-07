#include <iostream>
#include <fstream>
#include <string>
#include "tree.h"
#include "node.h"

int main(int argc, char** argv) {

    
    if (argc > 2)   // Check for too many arguments
    {
        std::cout << "Too many arguments" << std::endl; // Error message for too many arguments
        return 0;
    }

    
    if (argc == 2) // Check if file name given
    {
        
        std::string fileName = argv[1]; // Take in file name argument
        std::ifstream inFile;  // Open file with added file extension
        inFile.open(fileName + ".sp2020");

        // if the file exists
        if (inFile)
        {
            Tree binaryTree;  // Create tree

            binaryTree.root = binaryTree.buildTree(inFile);  // Populate tree from input file
            binaryTree.traverseInorder(binaryTree.root, fileName); // Traverse tree inorder and print to $filename.inorder
            binaryTree.traversePostorder(binaryTree.root, fileName);  // Traverse tree postorder and print to $filename.postorder
            binaryTree.traversePreorder(binaryTree.root, fileName);  // Traverse tree preorder and print to $filename.preorder

            
            inFile.close();   // Closing the input file

            return 0;
        }

        // if the file does not exists
        else
        {
            // Error message for file not found
            std::cout << '"' << fileName + ".sp2020" << '"' << " could not be found" << std::endl;
            return 0;
        }
    }

    // Checking for no file name given
    if (argc == 1)
    {
        
        std::ofstream tempFile;  // Creating a temporary file to hold console input
        tempFile.open("tree.temp", std::ios::trunc); // Overwrites if file already exists

        
        std::string word = ""; // Helper string variable

        // Looping until EOF is reached
        while (std::cin >> word)
            tempFile << (word + ' ');

        
        tempFile.close();  // Closing temporary file

        
        std::ifstream inFile;  // New input file filled with console input
        inFile.open("tree.temp", std::ios::in);

        
        if (inFile)  // Confirm the file exists
        {
            Tree binaryTree;            // Create tree

            binaryTree.root = binaryTree.buildTree(inFile);  // Populate tree from input file
            binaryTree.traverseInorder(binaryTree.root, "out");  // Traverse tree inorder and print to out.inorder
            binaryTree.traversePostorder(binaryTree.root, "out");  // Traverse tree postorder and print to out.postorder
            binaryTree.traversePreorder(binaryTree.root, "out");  // Traverse tree preorder and print to out.preorder

            
            inFile.close(); // Closing input file

            return 0;
        }

        // Handling temporary file not found
        else
        {
            // Error message for temporary file not found
            std::cout << "Temporary file could not be found" << std::endl;
            return 0;
        }

    }


    return 0;
}

	