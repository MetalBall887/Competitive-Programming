#include <bits/stdc++.h>
//d[i][j] - the number of ways for i-th contestant to get j points. we can calculate this with prefix sums if we will be 
//able to calculate all possible score assignments for one Y/N mask. Where it is N, the score must be 0, otherwise it must be
//1..p[k], k is 0,1,2. We xan consider all possible distributions by stars&bars technique, bouding by maximum can be done by
//the principle of inclusion-exclusion, where we can assume this contestant got more points for some exact problem than
//he could by simply giving p[k] + 1 "extra" points and calculating the same distributions.
using namespace std;

typedef long long ll;
 
const ll N = 1e6, MOD = 1e9 + 7;

ll d[2][2 * N];

struct SRMIntermissionPhase {

	ll C (ll x, ll c) {
		if (x < 0) return 0;
		if (c == 1) return 1;
		if (c == 2) return x + 1;
		return ((x + 1) * (x + 2) / 2) % MOD;
	}

	ll ways (string s, vector <int> p, ll x) {
		ll cnt = count_if (s.begin(), s.end(), [&] (char c) {return c == 'Y';});
		for (ll i = 0; i < 3; i++) {
			if (s[i] == 'N') p[i] = 1e9;
		}
		if (!cnt) return x == 0;
		x -= cnt;

		ll sum = C (x, cnt) - C (x - p[0], cnt) - C (x - p[1], cnt) - C (x - p[2], cnt) + 3 * MOD;
		sum += C (x - p[0] - p[1], cnt) + C (x - p[0] - p[2], cnt) + C (x - p[1] - p[2], cnt);
		sum -= C (x - p[0] - p[1] - p[2], cnt) + MOD;

		return sum % MOD;
	}
	ll countWays (vector <int> p, vector <string> s) {
		int n = s.size ();
		reverse (s.begin(), s.end());
		ll sm = p[0] + p[1] + p[2];
		d[0][0] = ways (s[0], p, 0);
		for (ll i = 1; i <= sm; i++) {
			d[0][i] = ways (s[0], p, i) + d[0][i-1];
			if (d[0][i] >= MOD) d[0][i] -= MOD;
		}

		for (ll i = 1; i < n; i++) {
			int k = i & 1;
			d[k][0] = 0;
			for (ll j = 1; j <= sm; j++) {
				d[k][j] = ways (s[i], p, j) * d[!k][j-1] % MOD + d[k][j-1];
				if (d[k][j] >= MOD) d[k][j] -= MOD;
			}
		}
		n--;
		return d[n & 1][sm];
	}
};
