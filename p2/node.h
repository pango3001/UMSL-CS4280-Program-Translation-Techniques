// Name:    Jesse McCarville-Schueths
// Course:  4280
// Date:    Mar 24, 2021
// Project: P2
// File:    node.h

#ifndef NODE_H
#define NODE_H

#include "token.h"
#include <string>

class Node {

public:
	Node();
	Node(std::string name, unsigned int depth);
	unsigned int getDepth() { return depth; }
	std::string getName() { return name; }

	Node child[4];
	Node* childptr = child;


private:
	unsigned int depth;
	std::string name;


};

Node::Node() {

}

Node::Node(std::string name, unsigned int depth) {
	this->name = name;
	this->depth = depth;
}


#endif