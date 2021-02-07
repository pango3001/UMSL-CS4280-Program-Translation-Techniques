#include <iostream>
#include <fstream>
#include <string>
#include "tree.h"
#include "node.h"


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

        std::string string = "";

        while (std::cin >> string)
            tempFile << (string + ' ');


        tempFile.close();

        inFile.open("file.temp", std::ios::in);

        fileName = "p0_output";
        std::cout << "1 arg found" << std::endl;

    }


    if (argc == 2) {
        fileName = argv[1];
        inFile.open(fileName + ".sp2020");
    }

    if (inFile) {
        Tree binaryTree;

        binaryTree.root = binaryTree.buildTree(inFile);
        binaryTree.traverseInorder(binaryTree.root, fileName);
        binaryTree.traversePostorder(binaryTree.root, fileName);
        binaryTree.traversePreorder(binaryTree.root, fileName);

        inFile.close();
        
        std::ifstream f(fileName + ".preorder");

        if (f.is_open())
            std::cout << f.rdbuf();

    }

    else {
        std::cout << "Error: File not found." << std::endl;
        return 0;
    }

    return 0;
}