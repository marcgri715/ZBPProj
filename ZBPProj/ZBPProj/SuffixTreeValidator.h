#pragma once
class SuffixTreeValidator
{
private:
	char CurrentString[MAX_LENGTH];
	char GoodSuffixes[MAX_LENGTH];
	char BranchCount[MAX_LENGTH * 2] = { 0 };
public:
	SuffixTreeValidator();
	void validate();
	int walk_tree(int start_node, int last_char_so_far);
	~SuffixTreeValidator();
};

