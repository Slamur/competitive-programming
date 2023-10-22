#include "problem_lib.h"

int main(int argc, char **argv) {
	registerGen(argc, argv, 1);

	int minN = opt<int>("minN");
	int maxN = opt<int>("maxN");

	auto gen_test = [&]() {
		int n = rnd.next(minN, maxN);
		println(n);
	};

	gen_test();
}
