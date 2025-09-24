#include "problem_lib.h"

using answer_t = int;
 
void quit_answer(answer_t expected, answer_t actual, InStream & stream) {
    stream.quitf(
        _wa,
        "answer is not best: expected answer %d, found answer %d",
        expected, actual
    );
}
 
bool left_better(answer_t left, answer_t right) {
    
}
 
int main(int argc, char * argv[])
{
    registerTestlibCmd(argc, argv);

    // read input

    auto read_answer = [&](InStream & stream) {
        return answer_t{};
    };
 
    auto read_answer_from = [&](InStream & stream) {
        answer_t answer = read_answer(stream);
        
        stream.quitif(
            !stream.seekEof(),
            _pe,
            "Extra information in the file"
        );
        
        return answer;
    };

    // read answers (jury and participant)
    answer_t ja = read_answer_from(ans);
    answer_t pa = read_answer_from(ouf);
 
    if (left_better(pa, ja)) quit_answer(ja, pa, ans);
    if (left_better(ja, pa)) quit_answer(ja, pa, ouf);
 
    quitf(_ok, "OK (answer %d)", pa);
}
