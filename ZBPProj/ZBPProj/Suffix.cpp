#include "stdafx.h"
#include "Suffix.h"
#include "Globals.h"


Suffix::Suffix(int node, int start, int stop) : origin_node(node), first_char_index(start), last_char_index(stop)
{
}

// A suffix in the tree is denoted by a Suffix structure
// that denotes its last character.  The canonical
// representation of a suffix for this algorithm requires
// that the origin_node by the closest node to the end
// of the tree.  To force this to be true, we have to
// slide down every edge in our current path until we
// reach the final node.
void Suffix::Canonize()
{
	if (!Explicit()) {
		Edge edge = Edge::Find(origin_node, T[first_char_index]);
		int edge_span = edge.GetLastCharIndex() - edge.GetFirstCharIndex();
		while (edge_span <= (last_char_index - first_char_index)) {
			first_char_index = first_char_index + edge_span + 1;
			origin_node = edge.GetEndNode();
			if (first_char_index <= last_char_index) {
				edge = Edge::Find(edge.GetEndNode(), T[first_char_index]);
				edge_span = edge.GetLastCharIndex() - edge.GetFirstCharIndex();
			};
		}
	}
}

int Suffix::Explicit()
{
	return first_char_index > last_char_index;
}

int Suffix::Implicit()
{
	return last_char_index >= first_char_index;
}

int Suffix::GetOriginNode()
{
	return origin_node;
}

int Suffix::GetFirstCharIndex()
{
	return first_char_index;
}

int Suffix::GetLastCharIndex()
{
	return last_char_index;
}

void Suffix::SetOriginNode(int value)
{
	origin_node = value;
}
void Suffix::SetFirstCharIndex(int value)
{
	first_char_index = value;
}
void Suffix::SetLastCharIndex(int value)
{
	last_char_index = value;
}

Suffix::~Suffix()
{
}
