#include "testlib.h"
#include <utility>
#include <cmath>
#include <set>
#include <vector>
using namespace std;

using ll = long long;
using vi = vector<int>;

const bool SPACE_SEP = false, EOLN_SEP = true;

int read_int(int min_value, int max_value, string const& name, bool separator = EOLN_SEP) {
    int result = inf.readInt(min_value, max_value, name);

    if (EOLN_SEP == separator) inf.readEoln();
    else inf.readSpace();

    return result;
}

int read_int_spaced(int min_value, int max_value, string const& name) {
    return read_int(min_value, max_value, name, false);
}

vi read_ints(int size, int min_value, int max_value, string const& name) {
    vi result = inf.readInts(size, min_value, max_value, name);
    inf.readEoln();
    return result;
};

template <typename T, typename L>
void ensure_limits(const string& name, const T& value, const L& min_value, const L& max_value) {
    ensuref(
        min_value <= value && value <= max_value,
        "Expected %s in [%d, %d], but found %d",
        name.c_str(), min_value, max_value, value
    );
}

int main(int argc, char* argv[])
{
	registerValidation(argc, argv);
	
	const int MIN_N = 1, MAX_N = 1e6;

	struct group_data { int maxN; }
   
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
