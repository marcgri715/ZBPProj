#include "stdafx.h"
#include "Edge.h"
#include "Globals.h"


Edge::Edge()
{
}

// I create new edges in the program while walking up
// the set of suffixes from the active point to the
// endpoint.  Each time I create a new edge, I also
// add a new node for its end point.  The node entry
// is already present in the Nodes[] array, and its
// suffix node is set to -1 by the default Node() ctor,
// so I don't have to do anything with it at this point.
Edge::Edge(int init_first, int init_last, int parent_node)
{
	first_char_index = init_first;
	last_char_index = init_last;
	start_node = parent_node;
	end_node = Node::Count++;
}

// A given edge gets a copy of itself inserted into the table
// with this function.  It uses a linear probe technique, which
// means in the case of a collision, we just step forward through
// the table until we find the first unused slot.
void Edge::Insert()
{
	int i = Hash(start_node, T[first_char_index]);
	while (Edges[i].start_node != -1)
		i = ++i % HASH_TABLE_SIZE;
	Edges[i] = *this;
}

// Removing an edge from the hash table is a little more tricky.
// You have to worry about creating a gap in the table that will
// make it impossible to find other entries that have been inserted
// using a probe.  Working around this means that after setting
// an edge to be unused, we have to walk ahead in the table,
// filling in gaps until all the elements can be found.
//
// Knuth, Sorting and Searching, Algorithm R, p. 527
void Edge::Remove()
{
	int i = Hash(start_node, T[first_char_index]);
	while (Edges[i].start_node != start_node ||
		Edges[i].first_char_index != first_char_index)
		i = ++i % HASH_TABLE_SIZE;
	for (;;) {
		Edges[i].start_node = -1;
		int j = i;
		for (;;) {
			i = ++i % HASH_TABLE_SIZE;
			if (Edges[i].start_node == -1)
				return;
			int r = Hash(Edges[i].start_node, T[Edges[i].first_char_index]);
			if (i >= r && r > j)
				continue;
			if (r > j && j > i)
				continue;
			if (j > i && i >= r)
				continue;
			break;
		}
		Edges[j] = Edges[i];
	}
}

// When a suffix ends on an implicit node, adding a new character
// means I have to split an existing edge.  This function is called
// to split an edge at the point defined by the Suffix argument.
// The existing edge loses its parent, as well as some of its leading
// characters.  The newly created edge descends from the original
// parent, and now has the existing edge as a child.
//
// Since the existing edge is getting a new parent and starting
// character, its hash table entry will no longer be valid.  That's
// why it gets removed at the start of the function.  After the parent
// and start char have been recalculated, it is re-inserted.
//
// The number of characters stolen from the original node and given
// to the new node is equal to the number of characters in the suffix
// argument, which is last - first + 1;
int Edge::SplitEdge(Suffix &s)
{
	Remove();
	Edge* new_edge =
		new Edge(first_char_index,
		first_char_index + s.GetLastCharIndex() - s.GetFirstCharIndex(),
		s.GetOriginNode());
	new_edge->Insert();
	Nodes[new_edge->end_node].SetSuffixNode(s.GetOriginNode());
	first_char_index += s.GetLastCharIndex() - s.GetFirstCharIndex() + 1;
	start_node = new_edge->end_node;
	Insert();
	return new_edge->end_node;
}

// The whole reason for storing edges in a hash table is that it
// makes this function fairly efficient.  When I want to find a
// particular edge leading out of a particular node, I call this
// function.  It locates the edge in the hash table, and returns
// a copy of it.  If the edge isn't found, the edge that is returned
// to the caller will have start_node set to -1, which is the value
// used in the hash table to flag an unused entry.
Edge Edge::Find(int node, int c)
{
	int i = Hash(node, c);
	for (;;) {
		if (Edges[i].start_node == node)
			if (c == T[Edges[i].first_char_index])
				return Edges[i];
		if (Edges[i].start_node == -1)
			return Edges[i];
		i = ++i % HASH_TABLE_SIZE;
	}
}

// Edges are inserted into the hash table using this hashing
// function.
int Edge::Hash(int node, int c)
{
	return ((node << 8) + c) % HASH_TABLE_SIZE;
}

int Edge::GetFirstCharIndex()
{
	return first_char_index;
}

int Edge::GetLastCharIndex()
{
	return last_char_index;

}

int Edge::GetEndNode()
{
	return end_node;
}

int Edge::GetStartNode()
{
	return start_node;
}
void Edge::SetFirstCharIndex(int value)
{
	first_char_index = value;
}

void Edge::SetLastCharIndex(int value)
{
	last_char_index = value;
}

void Edge::SetEndNode(int value)
{
	end_node = value;
}

void Edge::SetStartNode(int value)
{
	start_node = value;
}

Edge::~Edge()
{
}
