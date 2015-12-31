// This program asks you for a line of input, then
// creates the suffix tree corresponding to the given
// text. Additional code is provided to validate the
// resulting tree after creation.
//
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string.h>
#include <cassert>
#include <string>
#include "Edge.h"
#include "SuffixTree.h"
#include "SuffixTreeValidator.h"
#include "Globals.h"

using std::cout;
using std::cin;
using std::cerr;
using std::setw;
using std::flush;
using std::endl;



// This routine prints out the contents of the suffix tree
// at the end of the program by walking through the
// hash table and printing out all used edges.  It
// would be really great if I had some code that will
// print out the tree in a graphical fashion, but I don't!
//

void dump_edges(int current_n)
{
	cout << " Start  End  Suf  First Last  String\n";
	for (int j = 0; j < HASH_TABLE_SIZE; j++) {
		Edge *s = Edges + j;
		if (s->GetStartNode() == -1)
			continue;
		cout << setw(5) << s->GetStartNode() << " "
			<< setw(5) << s->GetEndNode() << " "
			<< setw(3) << Nodes[s->GetEndNode()].GetSuffixNode() << " "
			<< setw(5) << s->GetFirstCharIndex() << " "
			<< setw(6) << s->GetLastCharIndex() << "  ";
		int top;
		if (current_n > s->GetLastCharIndex())
			top = s->GetLastCharIndex();
		else
			top = current_n;
		for (int l = s->GetFirstCharIndex();
			l <= top;
			l++)
			cout << T[l];
		cout << "\n";
	}
}

int main()
{
	SuffixTree* suffixTree = new SuffixTree();
	SuffixTreeValidator* suffixTreeValidator = new SuffixTreeValidator();

	cout << "Normally, suffix trees require that the last\n"
		<< "character in the input string be unique.  If\n"
		<< "you don't do this, your tree will contain\n"
		<< "suffixes that don't end in leaf nodes.  This is\n"
		<< "often a useful requirement. You can build a tree\n"
		<< "in this program without meeting this requirement,\n"
		<< "but the validation code will flag it as being an\n"
		<< "invalid tree\n\n";
	cout << "Enter string: " << flush;
	cin.getline(T, MAX_LENGTH - 1);
	N = strlen(T) - 1;
	//
	// The active point is the first non-leaf suffix in the
	// tree.  We start by setting this to be the empty string
	// at node 0.  The AddPrefix() function will update this
	// value after every new prefix is added.
	//
	Suffix active(0, 0, -1);  // The initial active prefix
	for (int i = 0; i <= N; i++)
		suffixTree->AddPrefix(active, i);
	//
	// Once all N prefixes have been added, the resulting table
	// of edges is printed out, and a validation step is
	// optionally performed.
	//
	dump_edges(N);
	cout << "Would you like to validate the tree?"
		<< flush;
	std::string s;
	getline(cin, s);
	if (s.size() > 0 && s[0] == 'Y' || s[0] == 'y')
		suffixTreeValidator->validate();
	return 1;
};