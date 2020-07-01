#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Let d_k[i][j] be the number of traces from node i to node j with length exactly k. This dp can be found by matrix exponentiation trick.
//Then let d_k[n+i][j] be the number of traces from i to j with length smaller than k. Then d_k[n+i][j] = d_k-1[i][j] + d_k-1[n+i][j], which can also be added
//to dp matrix and exponentiated. Don't forget that nodes themselves might count as cycles with length 0.
 
using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

ll n, mod;

struct Matrix {
	ll a[70][70];

	Matrix (ll x = 0) {
		memset (a, 0, sizeof (a));
		for (ll i = 0; i < n; i++) {
			a[i][i] = x;
		}
	}

	ll* operator[] (ll x) {
		return a[x];
	}

	Matrix operator* (Matrix b) {
		Matrix c;
		for (ll i = 0; i < n; i++)
			for (ll j = 0; j < n; j++) {
				for (ll k = 0; k < n; k++)
					c[i][j] += a[i][k] * b[k][j] % mod;
				c[i][j] %= mod;
			}

		return c;
	}

	vector<ll> operator* (vector <ll> x) {
		vector<ll> b (n);

		for (ll i = 0; i < n; i++) {
			for (ll j = 0; j < n; j++)
				b[i] += a[i][j] * x[j] % mod;
			b[i] %= mod;
		}

		return b;
	}
} orig;

struct TourCounting {
	ll countTours (vector <string> g, int k, int m) {
		n = g.size ();
		mod = m;

		orig = Matrix (2 * n);

		for (ll i = 0; i < n; i++) {
			orig[n+i][n+i] = orig[n+i][i] = 1;
			for (ll j = 0; j < n; j++) {
				orig[i][j] = (g[i][j] == 'Y');
			}
		}

		n *= 2;

		Matrix s (1);
		ll ans = 0;
		
		while (k) {
			if (k & 1) s = s * orig;
			orig = orig * orig;
			k >>= 1;
		}

		vector <ll> x (n);

		for (ll i = 0; i < n / 2; i++) {
			ans += s[n / 2 + i][i];
		}

		ans += mod - n / 2;

		return ans % mod;
	}
};
