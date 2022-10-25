#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;
using vi = vector<int>;

const int EOLN_SEP = 0, SPACE_SEP = 1;

int read_int(int min_value, int max_value, string const& name, int separator = EOLN_SEP) {
    int result = inf.readInt(min_value, max_value, name);

    if (EOLN_SEP == separator) inf.readEoln();
    else inf.readSpace();

    return result;
}

vi read_ints(int size, int min_value, int max_value, string const& name) {
    vi result = inf.readInts(size, min_value, max_value, name);
    inf.readEoln();
    return result;
};

template <typename T, typename L, typename R>
void ensure_limits(const string& name, const T& value, const L& min_value, const R& max_value) {
    ensuref(
        min_value <= value && value <= max_value,
        "Expected %s in [%d, %d], but found %d",
        name.c_str(), min_value, max_value, value
    );
}

int main(int argc, char* argv[])
{
    registerValidation(argc, argv);

    const int MAX_N = 16;
    const int MAX_MK = 1'000'000'000;
    const int MAX_A = 1'000'000'000;

    int n = read_int(1, MAX_N, "n", SPACE_SEP);
    int m = read_int(1, MAX_MK, "m", SPACE_SEP);
    int k = read_int(1, MAX_MK, "k");

    read_ints(n, 1, MAX_A, "a");

    inf.readEof();

    return 0;
}
