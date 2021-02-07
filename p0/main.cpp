#include <iostream>
#include <fstream>
#include <string>
#include "tree.h"
#include "node.h"


void printFileNotFound();
void tree(std::string, std::ifstream);

int main(int argc, char** argv) {

    if (argc > 2){
        std::cout << "Too many arguments" << std::endl;
        return 0;
    }



    std::string fileName;
    std::ifstream inFile;

    if (argc == 1) {

        std::ofstream tempFile;
        tempFile.open("file.temp", std::ios::trunc);

        std::string word = "";

        while (std::cin >> word)
            tempFile << (word + ' ');


        tempFile.close();

        inFile.open("file.temp", std::ios::in);

        fileName = "out";
        std::cout << "1 arg found" << std::endl;

    }


    if (argc == 2) {
        fileName = argv[1];

        inFile.open(fileName + ".sp2020");
        std::cout << "2 args found" << std::endl;
    }

    if (inFile) {

        Tree binaryTree;

        binaryTree.root = binaryTree.buildTree(inFile);
        binaryTree.traverseInorder(binaryTree.root, fileName);
        binaryTree.traversePostorder(binaryTree.root, fileName);
        binaryTree.traversePreorder(binaryTree.root, fileName);

        inFile.close();

        return 0;
    }

    else {
        printFileNotFound();
        return 0;
    }





    /*
    if (argc == 2)
    {
        
        std::string fileName = argv[1];
        std::ifstream inFile;
        inFile.open(fileName + ".sp2020");
        
        if (inFile)
        {
            
            Tree binaryTree;

            binaryTree.root = binaryTree.buildTree(inFile);
            binaryTree.traverseInorder(binaryTree.root, fileName);
            binaryTree.traversePostorder(binaryTree.root, fileName);
            binaryTree.traversePreorder(binaryTree.root, fileName);
            
            inFile.close();

            return 0;
        }

        else
        {
            printFileNotFound();
            return 0;
        }
    }

    if (argc == 1)
    {
        
        std::ofstream tempFile;
        tempFile.open("file.temp", std::ios::trunc);

        
        std::string word = "";

        while (std::cin >> word)
            tempFile << (word + ' ');

        
        tempFile.close();

        
        std::ifstream inFile;
        inFile.open("file.temp", std::ios::in);

        
        if (inFile)
        {
            
            Tree binaryTree;

            binaryTree.root = binaryTree.buildTree(inFile);
            binaryTree.traverseInorder(binaryTree.root, "out");
            binaryTree.traversePostorder(binaryTree.root, "out");
            binaryTree.traversePreorder(binaryTree.root, "out");
            
            
            inFile.close();

            return 0;
        }

        else
        {
            printFileNotFound();
            return 0;
        }

    }
    */
    return 0;
}


void printFileNotFound() {
    std::cout << "Error: File not found." << std::endl;
}

void tree(std::string fileName, std::ifstream inFile) {
    Tree binaryTree;

    binaryTree.root = binaryTree.buildTree(inFile);
    binaryTree.traverseInorder(binaryTree.root, fileName);
    binaryTree.traversePostorder(binaryTree.root, fileName);
    binaryTree.traversePreorder(binaryTree.root, fileName);
}

	