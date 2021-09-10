#include "testlib.h"
#include <iostream>
#include <cstdio>
#include <cassert>

using namespace std;

using ld = long double;
using vi = vector<int>;
using ll = long long;
using vll = vector<ll>;
using ii = pair<int, int>;
using vii = vector<ii>;
using vs = vector<string>;

template<typename T>
T read() {
    T value;
    cin >> value;
    return value;
}

int ri() {
    return read<int>();
}

ll rll() {
    return read<ll>();
}

string rs() {
    return read<string>();
}

const char ENDL = '\n';

template <typename T>
void print_all(const vector<T>& values, char sep = ' ') {
    for (size_t i = 0; i < values.size(); ++i) {
        if (i > 0) cout << sep;
        cout << values[i];
    }
    cout << ENDL;
}

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

void gen_test(int n, int a, int b) {
    cout << n << " " << a << " " << b << endl;
    string s = "";
    for (int i = 0; i < n; i++) {
        s += rnd.next(0, 1) == 0 ? "S" : "B";
    }
    cout << s << endl;
}

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>("n");
    int a = opt<int>("a");
    int b = opt<int>("b");
    gen_test(n, a, b);
}