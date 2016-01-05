#pragma once

#include "Node.h"

// When a new tree is added to the table, we step
// through all the currently defined suffixes from
// the active point to the end point.  This structure
// defines a Suffix by its final character.
// In the canonical representation, we define that last
// character by starting at a node in the tree, and
// following a string of characters, represented by
// first_char_index and last_char_index.  The two indices
// point into the input string.  Note that if a suffix
// ends at a node, there are no additional characters
// needed to characterize its last character position.
// When this is the case, we say the node is Explicit,
// and set first_char_index > last_char_index to flag
// that.
class Suffix
{
private:
	int origin_node;
	int first_char_index;
	int last_char_index;
public:
	Suffix(int node, int start, int stop);
	int Explicit();
	int Implicit();
	void Canonize();
	int GetOriginNode();
	int GetFirstCharIndex();
	int GetLastCharIndex();
	void SetOriginNode(int value);
	void SetFirstCharIndex(int value);
	void SetLastCharIndex(int value);
	~Suffix();
};