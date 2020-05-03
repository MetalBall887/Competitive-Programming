#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//d[l][r] - the best way to arrange cows, where the segments for each cow lies inside of [l;r]. Assume the last cow in this
//scenario eats the pie on position i. That means this pie was not eaten before, so for all previous cows r_x < i or i < l_x
//holds and we can divide these segments into two disjunct sets (the maximal value of which happened to be calculated in 
//d[l][i-1] and d[i+1][r]). The cow which will be eating the i-th pie will be easy to determine by mx[i][l][r] - the biggest
//weight of the cow, for which holds l <= l_x <= i <= r_x <= r.


using namespace __gnu_pbds;
 
#define N 200003
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int mx[310][310][310], d[310][310], a[310][310];
int n, m;


int main () {
	freopen ("pieaters.in", "r", stdin);
	freopen ("pieaters.out", "w", stdout);

	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int l, r, w;
		cin >> w >> l >> r;
		a[l][r] = w;
	}

	for (int k = 0; k < n; k++)
		for (int i = 1; i + k <= n; i++)
			for (int j = i; j <= i + k; j++) {
				int l = i, r = i + k;

				mx[j][l][r] = a[l][r];
				mx[j][l][r] = max ({mx[j][l][r], mx[j][l + 1][r], mx[j][l][r - 1]});
			}

	for (int k = 0; k < n; k++)
		for (int i = 1; i + k <= n; i++)
			for (int j = i; j <= i + k; j++) {
				int l = i, r = i + k;

				d[l][r] = max (d[i][r], d[l][j] + d[j + 1][r]);
				d[l][r] = max (d[l][r], d[l][j - 1] + d[j + 1][r] + mx[j][l][r]);
			}

	cout << d[1][n];
}
