#ifndef NODE_H_
#define NODE_H_
#include <string>
#include <set>

struct Node {
	std::set <std::string> data;	// set of values for this node
	std::string twoChars; 			// first two chars
	Node* left;        				// ptr to left child
	Node* right;       				// ptr to right child

	// Constructor
	Node(std::string data)
	{
		this->data.insert(data);
		this->twoChars = data.substr(0, 2);
		this->left = nullptr;
		this->right = nullptr;
	}
};

#endif