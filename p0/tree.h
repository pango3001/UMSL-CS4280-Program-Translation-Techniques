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
    void insert(std::string value);

private:
    Node* insert(Node* node, std::string chars);
    Node* empty(Node* node);

    void traverseInorder(Node* node, int level, std::ostream& output);
    void traversePostorder(Node* node, int level, std::ostream& output);
    void traversePreorder(Node* node, int level, std::ostream& output);

};

#endif