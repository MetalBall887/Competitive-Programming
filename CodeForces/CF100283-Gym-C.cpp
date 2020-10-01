#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//The dp transition part is straightforward, the tricky part is a "diamond" query. It can be precalculated in O(nm) and answered O(1). The technique is to
//rotate it so it will transform into a rectangle query
//-------
//--123--
//--456--
//--789--
//-------
//to
//----1-----
//---4-2----
//--7-5-3---
//---8-6----
//----9----- x'=x+y, y'=x-y
using namespace __gnu_pbds;
 
#define N 2000001
 
using namespace std;
 
 
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
ll d[100][200][200], n, m, t, g[100][100], p[200][200], s;
 
ll px, py, M = 100;
 
ll sum (ll x1, ll y1, ll x2, ll y2) {
	ll sum = p[x2][y2];
	if (x1) sum += MOD - p[x1-1][y2];
	if (y1) sum += MOD - p[x2][y1-1];
	if (x1 && y1) sum += p[x1-1][y1-1];
 
	return sum % MOD;
}
 
ll get (ll x, ll y, ll t) {
	ll i = x + y, j = x - y + M;
	return sum (max (i - t, 0LL), max (j - t, 0LL), min (i + t, n + m - 1), min (j + t, n + M - 1));
}
 
void calc (ll a[][200]) {
 
	for (ll i = 0; i < n + m; i++) {
		memset (p[i], 0, sizeof(p[i][0]) * (n + M));
	}
 
	for (ll i = 0; i < n; i++)
		for (ll j = 0; j < m; j++) {
			p[i+j][i-j+M] = a[i][j];
		}
 
	for (ll i = 0; i < n + m; i++)
		for (ll j = 0; j < n + M; j++) {
			if (i) p[i][j] += p[i-1][j];
			if (j) p[i][j] += p[i][j-1];
			if (i && j) p[i][j] += MOD - p[i-1][j-1];
			p[i][j] %= MOD;
		}
}
 
int main () {
	freopen ("treasures.in", "r", stdin);
 
	cin >> t;
	for (ll c = 1; c <= t; c++) {
		cin >> n >> m >> s;
 
		cin >> px >> py;
		px--, py--;
 
		for (ll i = 0; i < n; i++)
			for (ll j = 0; j < m; j++) {
				cin >> g[i][j];
				d[0][i][j] = g[i][j];
			}
 
		for (ll k = 1; k < s; k++) {
			calc (d[k-1]);
 
			for (ll i = 0; i < n; i++) {
				for (ll j = 0; j < m; j++) {
					d[k][i][j] = get (i, j, k);
				}
			}
		}
 
		cout << "Case " << c << ": " << d[s-1][px][py] << '\n';
 
	}
}
