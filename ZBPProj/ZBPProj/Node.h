#pragma once

////  The only information contained in a node is the
////  suffix link. Each suffix in the tree that ends
////  at a particular node can find the next smaller suffix
////  by following the suffix_node link to a new node.  Nodes
////  are stored in a simple array.
////
class Node
{
private:
	int suffix_node;
public:
	static int Count;
	Node();
	int GetSuffixNode();
	void SetSuffixNode(int value);
	~Node();
};