#include "problem_lib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int minN = 1, maxN = 1e9;
    
    struct group_data { 
        int maxN; 
        bool should_be_prime; 
        bool should_be_pow_2; 
        
        group_data(int maxN)
        : group_data(maxN, false, false)
        { }
        
        group_data(int maxN, bool should_be_prime, bool should_be_pow_2)
        : maxN(maxN)
        , should_be_prime(should_be_prime)
        , should_be_pow_2(should_be_pow_2)
        { }
        
        void validate_n(int n) const {
            if (should_be_prime) {
                ensuref(
                    is_prime(n),
                    "Expected prime n, but found %d",
                    n
                );
            }
            
            if (should_be_pow_2) {
                ensuref(
                    (n & (n - 1)) == 0,
                    "Expected n = 2**k, but found %d",
                    n
                );
            }
        }
    };
    
    const int e1 = 1e1, e3 = 1e3, e6 = 1e6;
   
	std::vector<group_data> groups = {
		group_data(maxN), // samples
		group_data(e1), // group 1
		group_data(e3), // group 2
		group_data(e6), // group 3,
		group_data(maxN, true, false), // group 4,
		group_data(maxN, false, true), // group 5
		group_data(maxN) // group 6
	};

	auto const& group = groups[group_index()];

	int n = inf.readInt(minN, group.maxN, "n");
    inf.readEoln();
    
    group.validate_n(n);

    inf.readEof();
}
