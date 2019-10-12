#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
//Any permutation we get are cyclic shifts without some elements in it. So usual trick is to double a permutation so that
//there will be all cyclic shifts as subsegments of length n and swapping two parts of a sequence becomes just moving our 
//sliding window with deleting elements with BIT. But for getting 100pts it's mot enough, you should reduce your BIT twice
//because apparently one half will repeat another and we nhave to keep only one.
#include <fstream>
#include <set>
#include <cstring>
#include <assert.h>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

ll n, p[1000001], inv[1000001];

struct BIT {
	ll t[1000010];

	void update (ll x, ll d) {
		for (; x <= n; x = (x | (x + 1)))
			t[x] += d;
	}

	ll get (ll r) {
		ll sum = 0;
		for (; r >= 0; r = (r & (r + 1)) - 1)
			sum += t[r];
		return sum;
	}

	ll get (ll l, ll r) {
		return get (r) - get (l - 1);
	}
} a;

int main () {

	ifstream fin ("permsort.in");
	ofstream fout ("permsort.out");

	fin >> n;

	for (ll i = 0; i < n; i++) {
		a.update (i, 1);
		fin >> p[i];
		inv[p[i] - 1] = i;
	}

	ll ans = inv[0] + 1;
	a.update (inv[0], -1);

	for (ll i = 0; i < n - 1; i++) {
		ll l = inv[i], r = inv[i+1];
		ans += a.get (r % n) + (r < l ? a.get (n - 1) : 0) - a.get (l - 1);
		a.update (inv[i + 1], -1);
	}

	fout << ans;

	fclose (stdout);
	fclose (stdin);
}
