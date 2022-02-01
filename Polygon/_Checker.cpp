#include "testlib.h"
#include <cstdio>
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

#define sz(v) ((int)((v).size()))
#define all(v) (v).begin(),(v).end()
#define JURY "Jury"
#define PARTICIPANT "Participant"

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

struct CheckInfo {
    TResult result;
    const char * author;

    CheckInfo(TResult _result, const char * _author)
    : result(_result)
    , author(_author)
    { }
};

void read_ints(vi & values, size_t size,
                InStream & stream) {
    values.resize(size, 0);
    for (size_t index = 0; index < size; ++index) {
        values[index] = stream.readInt();
    }
}

void int_range_check(
                int value,
                const char * name, int min_value, int max_value,
                CheckInfo & info) {
    if (value < min_value || value > max_value)
    {
        quitf(
            info.result,
            "%s: incorrect %s: found %d, but should be [%d; %d]",
            info.author, name, value, min_value, max_value
        );
    }
}

void indexed_int_range_check(
                int value, size_t index,
                const char * name, int min_value, int max_value,
                CheckInfo & info) {
    if (value < min_value || value > max_value)
    {
        quitf(
            info.result,
            "%s: incorrect %s at position %d: found %d, but should be [%d; %d]",
            info.author, name, index + 1, value, min_value, max_value
        );
    }
}

void indexes_range_check(vi & indexes, const char * name, int max_index, CheckInfo & info) {
    for (size_t i = 0; i < indexes.size(); ++i) {
        int index = indexes[i];
        indexed_int_range_check(index, i, name, 1, max_index, info);
    }
}

vi indexes_duplicate_check(vi & indexes, int max_index, CheckInfo & info) {
    vi used(max_index, -1);
    for (size_t i = 0; i < indexes.size(); ++i) {
        int index = indexes[i] - 1;
        if (used[index] != -1) {
            quitf(
                info.result,
                "%s: duplicate indexes %d at positions %d and %d",
                info.author, index + 1, used[index], i
            );
        }

        used[index] = i;
    }
    return used;
}

void indexes_strictly_sorted_check(vi & indexes, CheckInfo & info) {
    for (size_t i = 1; i < indexes.size(); ++i) {
        if (indexes[i - 1] >= indexes[i]) {
            quitf(
                info.result,
                "%s: indexes are not sorted: %d at position %d >= %d at position %d",
                info.author, indexes[i - 1], i, indexes[i], i + 1
            );
        }
    }
}

struct Input {

    Input()
    { }
};

Input read_input() {
    /*
    int n = inf.readInt();

    vi costs;
    read_ints(costs, n, inf);
    */
    return Input();
}

using answer_t = ll;

answer_t read_answer(Input & input, InStream & stream, CheckInfo & info)
{

}

answer_t read_answer_from(const char * source,
                        Input & input,
                        InStream & stream,
                        CheckInfo & info)
{
    answer_t answer = read_answer(input, stream, info);
    if (!stream.seekEof())
    {
        stream.quitf(info.result, "Extra information in the %s file", source);
    }
    return answer;
}

void quit_answer(answer_t expected, answer_t actual, CheckInfo & info) {
    quitf(
        info.result,
        "%s answer is not best: expected answer %lld, found answer %lld",
        info.author, expected, actual
    );
}

bool better(answer_t first, answer_t second) {

}

int main(int argc, char * argv[])
{
    registerTestlibCmd(argc, argv);

    Input input = read_input();

    CheckInfo jury(_fail, JURY);
    CheckInfo participant(_wa, PARTICIPANT);

    answer_t ja = read_answer_from("answer", input, ans, jury);
    answer_t pa = read_answer_from("output", input, ouf, participant);

    if (better(pa, ja)) quit_answer(ja, pa, jury);
    if (better(ja, pa)) quit_answer(ja, pa, participant);

    quitf(_ok, "OK (answer %lld)", pa);
}