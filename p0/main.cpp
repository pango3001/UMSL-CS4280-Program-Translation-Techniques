#include <iostream>
#include <fstream>
#include <string>
#include "tree.h"
#include "node.h"


void printInorder(std::string);
void printPreorder(std::string);
void printPostorder(std::string);


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

        std::cout << "test" << std::endl;
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

        printInorder(fileName);
        printPreorder(fileName);
        printPostorder(fileName);
    }

    else {
        std::cout << "Error: File not found." << std::endl;
        return 0;
    }

    return 0;
}

void printInorder(std::string fileName) {
    std::cout << "Inorder traversal:" << std::endl;
    std::ifstream f(fileName + ".inorder");

    if (f.is_open())
        std::cout << f.rdbuf();
}
void printPreorder(std::string fileName) {
    std::cout << "Preorder traversal:" << std::endl;
    std::ifstream f(fileName + ".preorder");

    if (f.is_open())
        std::cout << f.rdbuf();
}
void printPostorder(std::string fileName) {
    std::cout << "Postorder traversal:" << std::endl;
    std::ifstream f(fileName + ".postorder");

    if (f.is_open())
        std::cout << f.rdbuf();
}