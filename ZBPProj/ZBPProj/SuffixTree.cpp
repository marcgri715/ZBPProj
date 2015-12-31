#include "stdafx.h"
#include "SuffixTree.h"


SuffixTree::SuffixTree()
{
}

//
// This routine constitutes the heart of the algorithm.
// It is called repetitively, once for each of the prefixes
// of the input string.  The prefix in question is denoted
// by the index of its last character.
//
// At each prefix, we start at the active point, and add
// a new edge denoting the new last character, until we
// reach a point where the new edge is not needed due to
// the presence of an existing edge starting with the new
// last character.  This point is the end point.
//
// Luckily for use, the end point just happens to be the
// active point for the next pass through the tree.  All
// we have to do is update it's last_char_index to indicate
// that it has grown by a single character, and then this
// routine can do all its work one more time.
//

void SuffixTree::AddPrefix(Suffix &active, int last_char_index)
{
	int parent_node;
	int last_parent_node = -1;

	for (;;) {
		Edge edge;
		parent_node = active.GetOriginNode;
		//
		// Step 1 is to try and find a matching edge for the given node.
		// If a matching edge exists, we are done adding edges, so we break
		// out of this big loop.
		//
		if (active.Explicit()) {
			edge = Edge::Find(active.GetOriginNode, T[last_char_index]);
			if (edge.GetStartNode != -1)
				break;
		}
		else { //implicit node, a little more complicated
			edge = Edge::Find(active.GetOriginNode, T[active.GetFirstCharIndex]);
			int span = active.GetLastCharIndex - active.GetFirstCharIndex;
			if (T[edge.GetFirstCharIndex + span + 1] == T[last_char_index])
				break;
			parent_node = edge.SplitEdge(active);
		}
		//
		// We didn't find a matching edge, so we create a new one, add
		// it to the tree at the parent node position, and insert it
		// into the hash table.  When we create a new node, it also
		// means we need to create a suffix link to the new node from
		// the last node we visited.
		//
		Edge *new_edge = new Edge(last_char_index, N, parent_node);
		new_edge->Insert();
		if (last_parent_node > 0)
			Nodes[last_parent_node].SetSuffixNode(parent_node);
		last_parent_node = parent_node;
		//
		// This final step is where we move to the next smaller suffix
		//
		if (active.GetOriginNode == 0)
			active.GetFirstCharIndex++;
		else
			active.GetOriginNode = Nodes[active.GetOriginNode].suffix_node;
		active.Canonize();
	}
	if (last_parent_node > 0)
		Nodes[last_parent_node].SetSuffixNode(parent_node);
	active.GetLastCharIndex++;  //Now the endpoint is the next active point
	active.Canonize();
};

SuffixTree::~SuffixTree()
{
}
