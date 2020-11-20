#include "testlib.h"
#include <utility>
#include <cmath>
#include <set>
#include <vector>
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

const int MAX_N = 300'000, maxT = 1'000'000'000;

class group_data {
public:
    int minN, maxN;
    int minK, maxK;

    group_data() : group_data(MAX_N) { }

    group_data(int maxN) : group_data(1, maxN) { }

    group_data(int minN, int maxN) : group_data(minN, maxN, 1, maxN) { }

    group_data(int minN, int maxN, int minK, int maxK)
    : minN(minN), maxN(maxN), minK(minK), maxK(maxK)
    { }
};

int main(int argc, char* argv[])
{
	registerValidation(argc, argv);

    group_data groups[] = {
        group_data(10),// sample
        group_data(3, 3, 1, 1), // k = 1, n = 3
        group_data(3, 3, 2, 3), // k > 1, n = 3
        group_data(1, MAX_N, 2, 2), // k == 2
        group_data(), // k == n
        group_data(), // a[j] >= t / 2
        group_data(100), // n <= 100
        group_data(101, 3000), // 101 <= n <= 3000
        group_data(3001, MAX_N) // n <= 3e5
    };

    int group_index = (validator.group() == "") ? stoi(validator.group()) : 9;
    auto const& group = groups[group_index];

    int n = read_int(group.minN, group.maxN, "n", SPACE_SEP);

    int t = read_int(1, maxT, "t", SPACE_SEP);

    int maxK = min(n, group.maxK);
    int k = read_int(group.minK, maxK, "k");

    int minA = (5 == group_index ? t / 2 : 1);
    read_ints(n, minA, t, "a");

    inf.readEof();

	return 0;
}