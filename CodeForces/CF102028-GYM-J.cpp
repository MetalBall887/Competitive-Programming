#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

//For each pair of carpets removed the answer can be bounded the number of cells that only one of this carpets covers (which can be counted independently). Also we
//need to include cells covered by both carpets from the pair but not more ("common" cells). If the cell is covered by two carpets, we found one pair with a common
//cell, otherwise it does not contribute. Thus, the number of pairs with common cells is limited by the number of cells. Process such pairs independently.
//For other pairs our bound is enough. The last problem is for each cell covered by two carpets determine the corresponding pair of carpets quickly. The one way
//is to use hashing and rectangle updates.
 
using namespace __gnu_pbds;
 
#define N 2000001
 
using namespace std;
 
 
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
ull area[1502][1502], p[1502][1502], n, m, t;
ull sum_hash[1502][1502];
ull hs[N];
 
unordered_map<ll, int> inter;
 
mt19937 rng;
 
struct Rect {
	int xl, xr, yl, yr;
} a[N];
 
void update (ull a[][1502], int x1, int y1, int x2, int y2, ull v) {
	a[x1][y1] += v, a[x2+1][y2+1] += v;
	a[x1][y2+1] -= v, a[x2+1][y1] -= v;
}
 
void calc (ull a[][1502]) {
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++) {
			if (i) a[i][j] += a[i-1][j];
			if (j) a[i][j] += a[i][j-1];
			if (i && j) a[i][j] -= a[i-1][j-1];
		}
}
 
void reset (ull a[][1502]) {
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++) {
			a[i][j] = 0;
		}
}
 
int main () {
	ios::sync_with_stdio(0);
	cin.tie(0);
 
	cin >> t;
 
	while (t--) {
		cin >> n >> m;
		
		inter.clear ();
		reset (p), reset (sum_hash), reset (area);
		ull ans = 0, all = 0;
 
		for (int i = 0; i < n; i++) {
			int xl, xr, yl, yr;
			cin >> xl >> xr >> yl >> yr;
			xl--, xr--, yl--, yr--;
			a[i].xl = xl, a[i].xr = xr;
			a[i].yl = yl, a[i].yr = yr;
 
			hs[i] = uniform_int_distribution <ll> (0, 1LL << 60) (rng);
			update (p, xl, yl, xr, yr, 1);
			update (sum_hash, xl, yl, xr, yr, hs[i]);
		}
 
		calc (p), calc (sum_hash);
 
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < m; j++) {
				if (p[i][j] <= 2) inter[sum_hash[i][j]]++;
				if (p[i][j]) all++;
			}
		}
 
		for (int i = 0; i < n; i++) {
			int x = inter[hs[i]];
			update (area, a[i].xl, a[i].yl, a[i].xr, a[i].yr, inter[hs[i]]);
			inter.erase (hs[i]);
			hs[i] = x;
		}
 
		calc (area);
 
		sort (hs, hs + n);
 
		ans = hs[n-1] + hs[n-2];
 
		for (int i = 0; i < m; i++)
			for (int j = 0; j < m; j++) {
				if (p[i][j] == 2) {
					ans = max (ans, inter[sum_hash[i][j]] + area[i][j]);
				}
			}
 
		cout << all - ans << '\n';
	}
}
