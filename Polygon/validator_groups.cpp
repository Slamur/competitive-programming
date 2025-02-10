#include "problem_lib.h"

int main(int argc, char* argv[])
{
	registerValidation(argc, argv);
	
	const int minN = 1, maxN = 1e6;

	struct group_data { int maxN; };
   
	vector<group_data> groups = {
		{maxN}, // samples
		{100}, // group 1
		{1e4}, // group 2
		{minN} // group 3
	};

	int group_index = (validator.group() != "") ? stoi(validator.group()) : 0;
	auto const& group = groups[group_index];

	int n = read_int(minN, group.maxN, "n");
	inf.readEof();

	return 0;
}
