#include "testlib.h"_Validator
#include <vector>
#include <utility>
#include <cmath>
#include <set>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

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

int main(int argc, char* argv[])
{
	registerValidation(argc, argv);

    struct data { int maxN, maxC; };

    constexpr data groups[] = {
        { 500, 500 },
        { 300'000, 300'000 },
        { 300'000, 1000'000'000 },
    };

    auto const& group = groups[map<string, int>{ { "2", 1 }, { "3", 2 } }[validator.group()]];

    int n = read_int(1, group.maxN, "n", SPACE_SEP);
    int k = read_int(1, n, "k");

    read_ints(n, 0, group.maxC, "c");

    inf.readEof();

	return 0;
}