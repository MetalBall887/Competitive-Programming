#include <bits/stdc++.h>
//https://codeforces.com/blog/entry/59968
 
#define N 1000001
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

ll n, l, wmax, ans;

vector <int> a, b;


int main () {
	cin >> n >> l >> wmax;

	for (int i = 0; i < n; i++) {
		int x, v;
		cin >> x >> v;

		if (v == 1) {
			a.push_back (x);
		} else {
			b.push_back (x);
		}
	}

	sort (a.begin(), a.end());
	sort (b.begin(), b.end());

	int ptr = 0;

	for (int i = 0; i < a.size (); i++) {
		while (ptr < b.size () && abs (a[i] + b[ptr] + l) >= wmax * (b[ptr] + l - a[i]))
			ptr++;
		ans += b.size () - ptr;
	}

	cout << ans;
}
