#pragma once

class SuffixTreeValidator
{
public:
	SuffixTreeValidator();
	void validate();
	int walk_tree(int start_node, int last_char_so_far);
	~SuffixTreeValidator();
};

