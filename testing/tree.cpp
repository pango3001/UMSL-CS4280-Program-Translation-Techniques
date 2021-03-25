// Name:    Jesse McCarville-Schueths
// Course:  4280
// Date:    Feb 7, 2021
// Project: P0
// File:    tree.cpp

// Disclaimer: a good chunk of this code was found online 
//			   but was altered by me to fit the 
//			   requirements of this project

#include "tree.h"

// Constructor
Tree::Tree() {				
	root = NULL;
}

// Destructor
Tree::~Tree() {				
	root = remove(root);	// Removes entire binary tree 
}

// Builds tree based on first to chars of each string inputted
Node* Tree::buildTree(std::istream& input) {  
	std::string string;

	while (input >> string)	{	// loops through all strings
		this->insert(string);
	}
	return root;
}

// inserts chars into tree
void Tree::insert(std::string chars) {
	root = insert(root, chars);
}

// makes preorder traverse file
void Tree::traversePreorder(Node* node, std::string filename) {
	filename += ".preorder";
	std::ofstream outFile;
	outFile.open(filename, std::ios::trunc);

	traversePreorder(node, 0, outFile);
}

// makes inorder traverse file
void Tree::traverseInorder(Node* node, std::string filename) {
	filename += ".inorder";
	std::ofstream outFile;
	outFile.open(filename, std::ios::trunc);

	traverseInorder(node, 0, outFile);
}

// makes postorder traverse file
void Tree::traversePostorder(Node* node, std::string filename) {
	filename += ".postorder";
	std::ofstream outFile;
	outFile.open(filename, std::ios::trunc);

	traversePostorder(node, 0, outFile);
}

//inserts string into tree depending on first two chars of string
Node* Tree::insert(Node* node, std::string chars) {
	if (node == NULL) return new Node(chars);

	if (chars.substr(0, 2) < node->twoChars)   // substr(0, 2) is for the first two chars of string
		node->left = insert(node->left, chars);
	
	else if (chars.substr(0, 2) > node->twoChars)
		node->right = insert(node->right, chars);

	else if (chars.substr(0, 2) == node->twoChars)
		node->data.insert(chars);

	return node;
}

// Deletes tree's nodes
Node* Tree::remove(Node* node) {
	if (node == NULL)
		return NULL;

	remove(node->left);
	remove(node->right);
	delete node;

	return NULL;
}

// for outputing preorder traversals
void Tree::traversePreorder(Node* node, int level, std::ostream& output) {
	if (node == NULL)
		return;

	std::string indents((level * 2), ' ');
	output << indents;
	for (auto string : node->data)
		output << string << " ";
	output << std::endl;

	traversePreorder(node->left, (level + 1), output);
	traversePreorder(node->right, (level + 1), output);
}

// for outputing inorder traversals
void Tree::traverseInorder(Node* node, int level, std::ostream& output) {
	if (node == NULL)
		return;

	traverseInorder(node->left, (level + 1), output);

	std::string indents((level * 2), ' ');
	output << indents;
	for (auto string : node->data)
		output << string << " ";
	output << std::endl;

	traverseInorder(node->right, (level + 1), output);
}

// for outputing postorder traversals
void Tree::traversePostorder(Node* node, int level, std::ostream& output) {
	if (node == NULL)
		return;

	traversePostorder(node->left, (level + 1), output);
	traversePostorder(node->right, (level + 1), output);

	std::string indents((level * 2), ' ');
	output << indents;
	for (auto string : node->data)
		output << string << " ";
	output << std::endl;
}