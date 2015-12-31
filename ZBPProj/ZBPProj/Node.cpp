#include "stdafx.h"
#include "Node.h"

//// The default ctor for Edge just sets start_node
//// to the invalid value.  This is done to guarantee
//// that the hash table is initially filled with unused
//// edges.
Node::Node()
{
	suffix_node = -1;
}

int Node::GetSuffixNode()
{
	return suffix_node;
}

void Node::SetSuffixNode(int value)
{
	suffix_node = value;
}

Node::~Node()
{
}
