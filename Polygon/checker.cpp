#include "problem_lib.h"

using answer_t = ll;
 
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
 
    if (better(pa, ja)) quit_answer(ja, pa, ans);
    if (better(ja, pa)) quit_answer(ja, pa, ouf);
 
    quitf(_ok, "OK (answer %lld)", pa);
}
