#include "problem_lib.h"

int main(int argc, char **argv) {
	registerGen(argc, argv, 1);

	int n = opt<int>("n");

	int minA = opt<int>("minA");
	int maxA = opt<int>("maxA");

	auto gen_test = [&]() {
		vi a(n);
		for (auto& v : a) v = rnd.next(minA, maxA);

		println(n);
		println(a);
	};

	gen_test();
}
