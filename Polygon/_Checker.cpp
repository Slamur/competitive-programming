#include "testlib.h"
#include <bits/stdc++.h>
 
using namespace std;
 
using ll = int64_t;
using ii = pair<int, int>;
using vi = vector<int>;
 
void int_range_check(
                int value,
                const string& name, int min_value, int max_value,
                InStream& stream) {
    stream.quitif(
        value < min_value || value > max_value,
        _wa,
        "incorrect %s: found %d, but should be [%d; %d]",
        name.c_str(), value, min_value, max_value
    );
}
 
void indexed_int_range_check(
                int value, size_t index,
                const string& name, int min_value, int max_value,
                InStream& stream) {
    stream.quitif(
        value < min_value || value > max_value,
        _wa,
        "incorrect %s at position %d: found %d, but should be [%d; %d]",
        name.c_str(), index + 1, value, min_value, max_value
    );
}
 
vi indexes_duplicate_check(vi & indexes, int max_index, InStream & stream) {
    vi used(max_index, -1);
    for (size_t i = 0; i < indexes.size(); ++i) {
        int index = indexes[i] - 1;
        
        stream.quitif(
            used[index] != -1,
            _wa,
            "duplicate indexes %d at positions %d and %d",
            index + 1, used[index], i
        );
 
        used[index] = i;
    }
    return used;
}
 
void indexes_strictly_sorted_check(vi & indexes, InStream& stream) {
    for (size_t i = 1; i < indexes.size(); ++i) {
        stream.quitif(
            indexes[i - 1] >= indexes[i],
            _wa,
            "indexes are not sorted: %d at position %d >= %d at position %d",
            indexes[i - 1], i, indexes[i], i + 1
        );
    }
}
 
struct Input {
    
    Input()
    { }
};
 
Input read_input() {
    // int n = inf.readInt();
    
    return Input();
}
 
using answer_t = ll;
 
answer_t read_answer(Input & input, InStream & stream)
{
    
}
 
answer_t read_answer_from(const string& source,
                        Input & input,
                        InStream & stream)
{
    answer_t answer = read_answer(input, stream);
    
    stream.quitif(
        !stream.seekEof(),
        _pe,
        "Extra information in the %s file", 
        source.c_str()
    );
    
    return answer;
}
 
void quit_answer(answer_t expected, answer_t actual, InStream & stream) {
    stream.quitf(
        _wa,
        "answer is not best: expected answer %lld, found answer %lld",
        expected, actual
    );
}
 
bool better(answer_t first, answer_t second) {
    
}
 
int main(int argc, char * argv[])
{
    registerTestlibCmd(argc, argv);
 
    Input input = read_input();
 
    answer_t ja = read_answer_from("answer", input, ans);
    answer_t pa = read_answer_from("output", input, ouf);
 
    if (better(pa, ja)) quit_answer(ja, pa, ans);
    if (better(ja, pa)) quit_answer(ja, pa, ouf);
 
    quitf(_ok, "OK (answer %lld)", pa);
}
