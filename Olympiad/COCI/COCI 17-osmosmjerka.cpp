#include <bits/stdc++.h>
//We use hashes to compare words. Also we can notice that the period of infinite words is the divisor of n*m, so for k > n*m
//first k symbols match <=> period matches, so we can claim k to be O(n*m). We can use binary lifting to quickly and simply
//count hashes of prefixes.
 
#define N 1000001
 
using namespace std;
 
typedef unsigned long long ull;
typedef long long ll;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

ll n, m, k;
ull p = 37, pm[N];
ull d[500][500][22];
string s[500];
map <ull, ll> mp;

ull query (ll x, ll y, ll h, ll v, ll k) {
	ull sum = 0, mult = 1;

	for (ll i = 0; i <= 20; i++) {
		if (k & (1 << i)) {
			sum += d[x][y][i] * mult;
			x = (x + n + (1 << i) % n * h) % n;
			y = (y + m + (1 << i) % m * v) % m;
			mult = mult * pm[i];
		}
	}

	return sum;
}

ll gcd (ll a, ll b) {
	if (!b) return a;
	return gcd (b, a % b);
}

int main () {
	cin >> n >> m >> k;
	k = min (k, n * m);

	for (ll i = 0; i < n; i++)
		cin >> s[i];

	pm[0] = p;

	for (ll i = 1; i <= 20; i++)
		pm[i] = pm[i-1] * pm[i-1];

	for (ll h = -1; h <= 1; h++)
		for (ll v = -1; v <= 1; v++) {
			if (!h && !v) continue;

			for (ll i = 0; i < n; i++)
				for (ll j = 0; j < m; j++) {
					d[i][j][0] = s[i][j] - 'a';
				}

			for (ll w = 0; w < 20; w++)
				for (ll i = 0; i < n; i++) {
					for (ll j = 0; j < m; j++) {
						ll nx = (i + n + (1 << w) % n * h) % n;
						ll ny = (j + m + (1 << w) % m * v) % m;
						d[i][j][w+1] = d[i][j][w] + d[nx][ny][w] * pm[w];
					}
				}

			for (ll i = 0; i < n; i++)
				for (ll j = 0; j < m; j++) {
					mp[query (i, j, h, v, k)]++;
				}
		}

	ll ans = 0, all = (n * m * 8) * (n * m * 8);
	for (auto a : mp) {
		ans += a.second * a.second;
	}

	cout << ans / gcd (ans, all) << "/" << all / gcd (ans, all);
}
