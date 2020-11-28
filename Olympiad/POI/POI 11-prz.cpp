#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Note that the first operation is just a cyclic shift and we in fact can translate this problem into sorting a sequence when the only operation we have is moving
//any element by 2 to the left. The algorithm we'll use is simple: assume numbers 1..i-1 already go one after another, move i to the left until it's as close as
//possible to the correct place. If there are >1 numbers between i-1 and i, move i. If there is a number between i-1 and i, for i < n-1 it will look like
//i-1 x i y, where you can shift x i y twice and obtain i-1 i y x. If i = n-1, then the locality looks like n-2 n n-1 1. If n is even, going a full circle will
//help, because the parity of the index will change, otherwise note that both operations don't change the parity of the permutation, so if our permutation is one
//swap away, it has a wrong parity and can't be sorted. Note that to move one element by two one requires 3*distance between i-1 and i, but it's 2a 1b move so
//only two instructions and 2 instructions to get rid of i-1 x i possibility and 2 instructions in the end, resulting in n*(n-1)/2 + 2n + 2 instructions total.
 
using namespace __gnu_pbds;
 
 
using namespace std;
 
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;

const int N = 2000001;
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

struct cyclic_array {
	vector <int> v;
	int shift, n;

	cyclic_array(int n) 
			: v (vector <int> (n)), shift (0), n (n) {}
	void make_b() { 
		shift = shift ? shift - 1 : n - 1;
	}
	void make_inv() { 
		shift = (shift == n - 1) ? 0 : shift + 1;
	}
	void make_a() { 
		int& a = v[shift % n];
		int& b = v[(shift + 1) % n];
		int& c = v[(shift + 2) % n];
		swap(b, c), swap(a, b);
	}

	int& operator[] (int x) {
		return v[(x + shift) % n];
	}
};

vector <pair<int, char>> s;

int n;

void add_a(cyclic_array& v) {
	v.make_a();
	if (!s.empty() && s.back().second == 'b') s.back().first++;
	else s.push_back({1, 'b'});
	if (s.back().first == n) s.pop_back();
}

void add_b(cyclic_array& v) {
	v.make_b();
	if (!s.empty() && s.back().second == 'a') s.back().first++;
	else s.push_back({1, 'a'});
	if (s.back().first == n) s.pop_back();
}

void add_inv(cyclic_array& v) {
	v.make_inv();
	if (!s.empty() && s.back().second == 'a') s.back().first = (s.back().first + n - 1) % n;
	else s.push_back({n - 1, 'a'});
	if (s.back().first == 0) s.pop_back();
}

int main () {
	cin >> n;

	cyclic_array v (n);

	for (int i = 0; i < n; i++) {
		cin >> v[i];
	}

	for (int i = 2; i <= n; i++) {
		while (v[2] != i) add_b(v);

		while (v[0] != i - 1 && v[1] != i - 1) {
			add_a(v), add_b(v), add_b(v);
		}

		if (v[0] == i - 1) {
			if (i >= n - 1) {
				if (n % 2 == 0) {
					while (v[1] != i - 1) {
						add_a(v), add_b(v), add_b(v);
					}
				} else {
					cout << "NIE DA SIE\n";
					return 0;
				}
			} else {
				add_inv(v), add_a(v), add_a(v);	
			}
		}
	}

	while (v[0] != 1) add_b(v);

	cout << s.size () << endl;

	for (auto a : s) {
		cout << a.first << a.second << ' ';
	}

	return 0;

}
