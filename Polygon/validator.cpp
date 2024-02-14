#include "problem_lib.h"

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

    const int MIN_N = 1, MAX_N = 1e6;
    const int MIN_A = 1, MAX_A = 1e9;
    const int MIN_Q = 1, MAX_Q = 3e5;

    int n = read_int(MIN_N, MAX_N, "n", SPACE_SEP);
    int q = read_int(MIN_Q, MAX_Q, "q");

    vi a = read_ints(n, MIN_A, MAX_A, "a");

    inf.readEof();

    return 0;
}
