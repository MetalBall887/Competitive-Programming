#include <bits/stdc++.h>
//https://hsin.hr/coci/archive/2009_2010/
 
#define N 1000001
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

ll n, k, a;

bitset <10000001> b;
vector <ll> v;

int main () {
	cin >> n >> k >> a;

	for (ll i = 2; i <= 10000000; i++) {
		if (!b[i]) {
			v.push_back (i);
			if (v.size () == k) break;
			for (ll j = i * i; j <= 10000000; j += i)
				b[j] = 1;
		}
		if (v.size () == k) break;
	}

	ll x = a - 1, x1, x2;

	for (ll i = 0; i < k; i++) {
		if (!x) x = v[i] % n;
		else {
			if (x <= v[i] % (n - 1)) x = (x + n - 1) % n;
			x = (x - (v[i] / (n - 1)) % n + n) % n;
		}
	}

	x1 = (x + 1) % n;
	x2 = (x + n - 1) % n;

	for (ll i = k - 1; i >= 0; i--) {
		if (x1 == v[i] % n) x1 = 0;
		else {
			x1 = (x1 + v[i] / (n - 1)) % n;
			if (x1 <= v[i] % (n - 1)) x1 = (x1 + 1) % n;
		}

		if (x2 == v[i] % n) x2 = 0;
		else {
			x2 = (x2 + v[i] / (n - 1)) % n;
			if (x2 <= v[i] % (n - 1)) x2 = (x2 + 1) % n;
		}
	}

	cout << x1 + 1 << ' ' << x2 + 1 << endl;
}
