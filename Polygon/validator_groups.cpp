#include "problem_lib.h"

int main(int argc, char* argv[])
{
	registerValidation(argc, argv);
	
	const int MIN_N = 1, MAX_N = 1e6;

	struct group_data { int maxN; };
   
	vector<group_data> groups = {
		{NAX_N}, // samples
		{100}, // group 1
		{1e4}, // group 2
		{MAX_N} // group 3
	};

	int group_index = (validator.group() != "") ? stoi(validator.group()) : 0;
	auto const& group = groups[group_index];

	int n = read_int(MIN_N, group.maxN, "n");
	inf.readEof();

	return 0;
}
