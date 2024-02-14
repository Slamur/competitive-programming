#include "problem_lib.h"

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
