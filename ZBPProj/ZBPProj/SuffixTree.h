#pragma once
#include "Suffix.h"

class SuffixTree
{
public:
	SuffixTree();
	void AddPrefix(Suffix &active, int last_char_index);
	~SuffixTree();
};

