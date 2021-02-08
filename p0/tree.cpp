// Name:    Jesse McCarville-Schueths
// Course:  4280
// Date:    Feb 7, 2021
// Project: P0
// File:    tree.cpp

#include "tree.h"

Tree::Tree() {
	root = NULL;
}

Tree::~Tree() {
	root = empty(root);
}


Node* Tree::buildTree(std::istream& input) {
	std::string string;

	while (input >> string)
	{
		this->insert(string);
	}
	return root;
}

void Tree::insert(std::string value) {
	root = insert(root, value);
}

void Tree::traverseInorder(Node* node, std::string filename) {
	filename += ".inorder";
	std::ofstream outFile;
	outFile.open(filename, std::ios::trunc);

	traverseInorder(node, 0, outFile);
}

void Tree::traversePostorder(Node* node, std::string filename) {
	filename += ".postorder";
	std::ofstream outFile;
	outFile.open(filename, std::ios::trunc);

	traversePostorder(node, 0, outFile);
}

void Tree::traversePreorder(Node* node, std::string filename) {
	filename += ".preorder";
	std::ofstream outFile;
	outFile.open(filename, std::ios::trunc);

	traversePreorder(node, 0, outFile);
}

Node* Tree::insert(Node* node, std::string chars) {
	if (node == NULL) return new Node(chars);
	if (chars.substr(0, 2) < node->twoChars)
		node->left = insert(node->left, chars);

	else if (chars.substr(0, 2) > node->twoChars)
		node->right = insert(node->right, chars);

	else if (chars.substr(0, 2) == node->twoChars)
		node->data.insert(chars);

	return node;
}


Node* Tree::empty(Node* node) {	  // Deletes tree's nodes
	if (node == NULL)
		return NULL;

	empty(node->left);
	empty(node->right);
	delete node;

	return NULL;
}

void Tree::traverseInorder(Node* node, int level, std::ostream& output) {
	if (node == NULL)
		return;

	traverseInorder(node->left, (level + 1), output);

	std::string indents((level * 2), ' ');
	output << indents;
	for (auto word : node->data)
		output << word << " ";
	output << std::endl;

	traverseInorder(node->right, (level + 1), output);
}

void Tree::traversePostorder(Node* node, int level, std::ostream& output) {
	if (node == NULL)
		return;

	traversePostorder(node->left, (level + 1), output);
	traversePostorder(node->right, (level + 1), output);

	std::string indents((level * 2), ' ');
	output << indents;
	for (auto word : node->data)
		output << word << " ";
	output << std::endl;
}

void Tree::traversePreorder(Node* node, int level, std::ostream& output) {
	if (node == NULL)
		return;

	std::string indents((level * 2), ' ');
	output << indents;
	for (auto word : node->data)
		output << word << " ";
	output << std::endl;

	traversePreorder(node->left, (level + 1), output);
	traversePreorder(node->right, (level + 1), output);
}