// Name:    Jesse McCarville-Schueths
// Course:  4280
// Date:    Feb 7, 2021
// Project: P0
// File:    tree.h

#ifndef TREE_H_
#define TREE_H_
#include "node.h"
#include <string>
#include <fstream>
#include <iostream>

class Tree {
public:
    Node* root;

    Tree();
    ~Tree();

    Node* buildTree(std::istream& input);
    void traverseInorder(Node* node, std::string filename);
    void traversePostorder(Node* node, std::string filename);
    void traversePreorder(Node* node, std::string filename);
    void insert(std::string chars);

private:
    Node* insert(Node* node, std::string chars);
    Node* remove(Node* node);

    void traverseInorder(Node* node, int level, std::ostream& output);
    void traversePostorder(Node* node, int level, std::ostream& output);
    void traversePreorder(Node* node, int level, std::ostream& output);

};

#endif