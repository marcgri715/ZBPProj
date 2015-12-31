#include "stdafx.h"
#include "SuffixTreeValidator.h"


SuffixTreeValidator::SuffixTreeValidator()
{
}

//
// The validation code consists of two routines.  All it does
// is traverse the entire tree.  walk_tree() calls itself
// recursively, building suffix strings up as it goes.  When
// walk_tree() reaches a leaf node, it checks to see if the
// suffix derived from the tree matches the suffix starting
// at the same point in the input text.  If so, it tags that
// suffix as correct in the GoodSuffixes[] array.  When the tree
// has been traversed, every entry in the GoodSuffixes array should
// have a value of 1.
//
// In addition, the BranchCount[] array is updated while the tree is
// walked as well.  Every count in the array has the
// number of child edges emanating from that node.  If the node
// is a leaf node, the value is set to -1.  When the routine
// finishes, every node should be a branch or a leaf.  The number
// of leaf nodes should match the number of suffixes (the length)
// of the input string.  The total number of branches from all
// nodes should match the node count.
//

void SuffixTreeValidator::validate()
{
	for (int i = 0; i < N; i++)
		GoodSuffixes[i] = 0;
	walk_tree(0, 0);
	int error = 0;
	for (int i = 0; i < N; i++)
		if (GoodSuffixes[i] != 1) {
		cout << "Suffix " << i << " count wrong!\n";
		error++;
		}
	if (error == 0)
		cout << "All Suffixes present!\n";
	int leaf_count = 0;
	int branch_count = 0;
	for (int i = 0; i < Node::Count; i++) {
		if (BranchCount[i] == 0)
			cout << "Logic error on node "
			<< i
			<< ", not a leaf or internal node!\n";
		else if (BranchCount[i] == -1)
			leaf_count++;
		else
			branch_count += BranchCount[i];
	}
	cout << "Leaf count : "
		<< leaf_count
		<< (leaf_count == (N + 1) ? " OK" : " Error!")
		<< "\n";
	cout << "Branch count : "
		<< branch_count
		<< (branch_count == (Node::Count - 1) ? " OK" : " Error!")
		<< endl;
}

int SuffixTreeValidator::walk_tree(int start_node, int last_char_so_far)
{
	int edges = 0;
	for (int i = 0; i < 256; i++) {
		Edge edge = Edge::Find(start_node, i);
		if (edge.GetStartNode != -1) {
			if (BranchCount[edge.GetStartNode] < 0)
				cerr << "Logic error on node "
				<< edge.GetStartNode
				<< '\n';
			BranchCount[edge.GetStartNode]++;
			edges++;
			int l = last_char_so_far;
			for (int j = edge.GetFirstCharIndex; j <= edge.GetLastCharIndex; j++)
				CurrentString[l++] = T[j];
			CurrentString[l] = '\0';
			if (walk_tree(edge.GetEndNode, l)) {
				if (BranchCount[edge.GetEndNode] > 0)
					cerr << "Logic error on node "
					<< edge.GetEndNode
					<< "\n";
				BranchCount[edge.GetEndNode]--;
			}
		}
	}
	//
	// If this node didn't have any child edges, it means we
	// are at a leaf node, and can check on this suffix.  We
	// check to see if it matches the input string, then tick
	// off it's entry in the GoodSuffixes list.
	//
	if (edges == 0) {
		cout << "Suffix : ";
		for (int m = 0; m < last_char_so_far; m++)
			cout << CurrentString[m];
		cout << "\n";
		GoodSuffixes[strlen(CurrentString) - 1]++;
		cout << "comparing: " << (T + N - strlen(CurrentString) + 1)
			<< " to " << CurrentString << endl;
		if (strcmp(T + N - strlen(CurrentString) + 1, CurrentString) != 0)
			cout << "Comparison failure!\n";
		return 1;
	}
	else
		return 0;
}

SuffixTreeValidator::~SuffixTreeValidator()
{
}
