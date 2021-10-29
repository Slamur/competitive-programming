#define NSTRESS

#ifdef STRESS

typedef uniform_int_distribution<> uid;
typedef mt19937 rnd_t;

void stress() {
	ll seed = 12345;
	bool with_time = true;
	if (with_time) seed += time(0);
	rnd_t rnd(seed);
	
	uid nGen(1, 10);
	uid aGen(0, 999);
	
	for (int it = 0; it < 100; ++it) {
		int n = nGen(rnd);
		
		vi a(n);
		for (int i = 0; i < n; ++i) {
			a[i] = aGen(rnd);
		}
		
		auto expected = get_brute_answer(n, a);
		auto actual = get_answer(n, a);
		
		auto print_ans = [&](ans_t ans) {
			print(ans);
		};
		
		if (expected != actual) {
			cout << "GOTCHA !!!" << endl;
			
			print(n);
			print_all(a);
			
			cout << "===" << endl;
			print_ans(expected);
			print_ans(actual);
			cout << "===" << endl;
			
			break;
		}
	}
}

#endif
