#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//We can binary search the answer. Here we will use meet-in-the-middle technique to reduce the number of elements we traverse
//Divide our set of primes into two roughly equal subsets, generate all numbers for both of them independently, sort
//then you can find out the number of products of pairs from both generated sequences less than or equal to some k
//with two pointers method.
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e15, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const ll N = 1e6, Z = 1e6;

ll n, k;
vector <ll> a, b;
vector <ll> p[2];

vector <ll> generate (vector <ll> p) {
	vector <ll> s (1, 1);
	vector <ll> v;

	for (ll x : p) {
		for (ll i : s) {
			ll k = i;

			while (k < 1e18 && k >= 0) {
				v.push_back (k);
				if (k < 1e18 / x) k *= x;
				else k = -1;
			}
		}

		s = move (v);
	}

	return move (s);
}

int main () {
	cin >> n;

	p[0].resize (n / 2 + n % 2);
	p[1].resize (n / 2);

	for (ll i = 0; i < n; i++)
		cin >> p[i & 1][i / 2];
	cin >> k;

	a = generate (p[0]);
	b = generate (p[1]);
	sort (a.begin(), a.end());
	sort (b.begin(), b.end());

	ll l = 0, r = 1e18;

	while (l < r) {
		ll mid = (l + r) / 2;

		int ptr = b.size () - 1;
		ll ans = 0;

		for (int i = 0; i < a.size (); i++) {
			while (ptr >= 0 && a[i] > mid / b[ptr]) ptr--;
			ans += ptr + 1;
		}

		if (ans >= k) r = mid;
		else l = mid + 1;
	}

	cout << l << endl;
}
