#ifndef _PROBLEM_LIB_H
#define _PROBLEM_LIB_H
 
#include "testlib.h"
#include <bits/stdc++.h>
 
using ld = long double;
using vi = std::vector<int>;
using ll = long long;
using vll = std::vector<ll>;
using ii = std::pair<int, int>;
using vii = std::vector<ii>;
using vs = std::vector<std::string>;
 
template<typename T>
T read() {
    T value;
    std::cin >> value;
    return value;
}
 
int ri() {
    return read<int>();
}
 
ll rll() {
    return read<ll>();
}
 
std::string rs() {
    return read<std::string>();
}
 
template <typename T>
std::vector<T> rv(int size) {
	std::vector<T> values(size);
	for (auto& value : values) value = read<T>();
	return values;
}
 
const char ENDL = '\n';
 
vii steps = {
    { 1, 0 }, { 0, -1 }, { -1, 0 }, { 0, 1 }
};
 
const int DOWN = 0, LEFT = 1, UP = 2, RIGHT = 3;
 
bool check_index(int index, int size) {
    return 0 <= index && index < size;
}
 
bool check_cell(int x, int n, int y, int m) {
    return check_index(x, n) && check_index(y, m);
}
 
bool is_prime(int x) {
    if (x < 2) return false;
    for (int d = 2; d * d <= x; ++d) {
        if (x % d == 0) return false;
    }
    return true;
}
 
int any_prime(int minX, int maxX) {
    vi variants;
    for (int x = minX; x <= maxX; ++x) {
        if (is_prime(x)) variants.push_back(x);
    }
    
    return rnd.any(variants);
}
 
int gcd(int a, int b) {
    return a == 0 ? b : gcd(b % a, a);
}
 
vll catalan(int max_n) {
    ensuref(
        max_n >= 1,
        "Expected max_n at least 1, but found %d",
        max_n
    );
    
    vll c(max_n + 1, 0);
    c[0] = 1;
    for (int n = 1; n <= max_n; ++n) {
        for (int left = 1; left <= n; ++left) {
            c[n] += c[left - 1] * c[n - left];
        }
    }
    
    return c;
}
 
// validator functions
 
template <typename T, typename L, typename R>
void ensure_limits(const std::string& name, const T& value, const L& min_value, const R& max_value) {
    ensuref(
        min_value <= value && value <= max_value,
        "Expected %s in [%d, %d], but found %d",
        name.c_str(), min_value, max_value, value
    );
}
 
#endif
