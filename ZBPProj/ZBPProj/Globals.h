#pragma once

#include "Edge.h"
#include "SuffixTree.h"
#include "stdafx.h"

//
// The maximum input string length this program
// will handle is defined here.  A suffix tree
// can have as many as 2N edges/nodes.  The edges
// are stored in a hash table, whose size is also
// defined here.
//
#define MAX_LENGTH 1000
#define HASH_TABLE_SIZE 2179  //A prime roughly 10% larger

//
// This is the hash table where all the currently
// defined edges are stored.  You can dump out
// all the currently defined edges by iterating
// through the table and finding edges whose start_node
// is not -1.
//

extern Edge Edges[HASH_TABLE_SIZE];

//
// The array of defined nodes.  The count is 1 at the
// start because the initial tree has the root node
// defined, with no children.
//

extern Node Nodes[MAX_LENGTH * 2];

//
// The input buffer and character count.  Please note that N
// is the length of the input string -1, which means it
// denotes the maximum index in the input buffer.
//

extern char T[MAX_LENGTH];
extern int N;

extern char CurrentString[MAX_LENGTH];
extern char GoodSuffixes[MAX_LENGTH];
extern char BranchCount[MAX_LENGTH * 2];