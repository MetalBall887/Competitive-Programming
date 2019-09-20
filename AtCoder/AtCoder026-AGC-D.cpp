#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
//Let's first solve this problem for a rectangle. Let si be the mask of i-th row. Assume it has some consequent cells of the 
//same color (in columns j and j+1). That means that (i+1, j) and (i+1, j+1) are already defined: there is only one possible
//coloring to not to create a bad square. (i+1, j) != (i, j), which means in rectangle on the left there is too only one 
//coloring: (i+1, j-1) != (i, j-1). Similarly on the other sides, we get the result that with our condition si = not(si+1)
//For all masks where all neighboring cells (notice that there are only two of them) are different we can match a mask 
//with the same condition, which means si = si+1 or si = not(si+1). Let's call such masks even. Those are masks of RBRBRB...
//and BRBRBRBR... dp[i][1] - the number of ways for a histogram  with uneven mask to be colored from the top to row i,
//dp[i][0] - the same number of ways but for even masks (since for each RB.. mask coloring we can invert all colors and 
//obtain BR.. mask coloring, we consider those two masks have the same numbers of ways). Here mask is the i-th row of
//histogram. Scanning line from top is done, adding new columns and merging some histograms in one when they have a common 
//column. Actualize - function for dp[i][0] to consider the current height of histogram relatively scanning line.
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

string s;

ll dp[100][2], last[100];

ll p[100], sz[100], n;

vector < pair <ll, ll> > v;

ll qpow (ll a, ll b) {
	ll s = 1;

	while (b) {
		if (b & 1) s = s * a % MOD;
		a = a * a % MOD;
		b /= 2;
	}

	return s;
}

ll find (ll x) {
	if (x == p[x]) return x;
	return p[x] = find (p[x]);
}

void actualize (ll x, ll y) {
	dp[x][0] = dp[x][0] * qpow (2, last[x] - y) % MOD;
	last[x] = y;
}

void unite (ll a, ll b) {
	a = find (a);
	b = find (b);

	if (a == b) return;

	if (sz[a] < sz[b]) swap (a, b);

	actualize (a, min (last[a], last[b]));
	actualize (b, min (last[a], last[b]));

	dp[a][1] = (dp[a][1] * (2 * dp[b][0] % MOD + dp[b][1]) % MOD) % MOD + 2 * dp[a][0] * (dp[b][0] + dp[b][1]) % MOD;
	dp[a][0] = dp[a][0] * dp[b][0] % MOD;

	p[b] = a;

	sz[a] += sz[b];
}

int main () {
	cin >> n;

	for (ll i = 0; i < n; i++) {
		ll h;

		scanf ("%lld", &h);

		last[i] = h;

		v.emplace_back (h, i);

		dp[i][0] = 1;
		dp[i][1] = 0;

		sz[i] = 1;
		p[i] = i;
	}

	sort (v.begin(), v.end());
	reverse (v.begin(), v.end());

	for (auto a : v) {

		if (a.second != n - 1 && last[a.second + 1] >= last[a.second]) {
			unite (a.second, a.second + 1);
		}
		if (a.second && last[a.second - 1] >= last[a.second]) {
			unite (a.second - 1, a.second);
		}
	}

	actualize (find (0), 1);

	cout << (2 * dp[find (0)][0] + dp[find (0)][1]) % MOD;
}
