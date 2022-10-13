#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;

const mod = 1e9 + 7;

class Matrix {
private:
	vector<int> values;
	int n, m;
public:
	Matrix(int n, int m)
	: values(n * m)
	, n(n)
	, m(m)
	{ }
	
	Matrix(const vector<vector<int>>& _values)
	: this(_values.size(), _values[0].size()) 
	{
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				get(i, j) = _values[i][j];
			}
		}
	}
	
	int& get(int x, int y) { return values[x * m + y]; }
	
	Matrix operator*(const Matrix& other) {
		Matrix res(n, other.m);
		
		for (int i = 0; i < n; ++i) {
			for (int k = 0; k < m; ++k) {
				for (int j = 0; j < other.m; ++j) {
					res.get(i, j) += get(i, k) * other.get(k, j);
					res.get(i, j) %= mod;
				}
			}
		}
		
		return res;
	}
};

Matrix binpow(const Matrix& base, ll power) {
	if (power == 0) {
		Matrix e(base.n, base.m);
		for (int i = 0; i < base.n; ++i) e.get(i, i) = 1;
		return e;
	}
	
	auto half = binpow(base, power >> 1);
	auto res = half * half;
	if (power % 2 == 1) {
		res = res * base;
	}
	
	return res;
}

int main() {
	ll n;
	cin >> n;
	
	auto get_answer = [&]() {
		if (n == 1) return 1;

		Matrix m({
			{ 2, 3, 1, 1 },
			{ 1, 0, 0, 0 },
			{ 0, 0, 1, 1 },
			{ 0, 0, 0, 1 }
		});
		
		Matrix a2(4, 1);
		for (int i = 0; i < 4; ++i) a2.get(i, 0) = 1;
		
		auto res = binpow(m, n - 2) * a2;
		return res.get(0, 0);
	}	
	
	cout << get_answer() << "\n";

	return 0;
}
