#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//For an i-th truck the lowest volume is needed if we put his ri stops between cities fi and si that way the maximum distance between two stops or enpoint and 
//closest stop is minimal. Note that it doesn't depend on ci, we can assume ci = 1 and then just multiply the volume by the actual ci. Let d[i][j][k] be the 
//minimal maximum distance between any two incident stops on the path between cities i and j where the number of stops is k. Then for an i-th truck the needed
//volume will be ci*d[fi][si][ri]. We can count this dp ny iterating the last stop, let last stop be r, then d[i][j][k] = max(d[i][r][k-1], a[j] - a[r]).
//Note that d[i][j][k] can't decrease with j increasing, so we can keep r where d[i][r][k-1] is the closest to a[j] - a[r] because that way the maximum will be
//the smallest. With this two-pointers optimisation we can calculate the table in O(n^3).
 
using namespace __gnu_pbds;
 
#define N 800003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int n, m, A, B;
 
int d[400][400][401], a[400];
 
int main () {
	ios::sync_with_stdio(0);
	cin.tie(0);
 
	cin >> n >> m;
 
	for (int i = 0; i < n; i++)
		cin >> a[i];
 
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) 
			d[i][j][0] = a[j] - a[i];
 
		for (int k = 1; k <= n; k++) {
			d[i][i][k] = 0;
 
			int r = i;
				
			for (int j = i + 1; j < n; j++) {
				while (d[i][r][k-1] < a[j] - a[r]) r++;
				d[i][j][k] = d[i][r][k-1];
				if (r > i) d[i][j][k] = min (d[i][j][k], a[j] - a[r-1]);
			}
		}
	}
 
	ll ans = 0;
 
	for (int i = 0; i < m; i++) {
		ll f, s, c, r;
		cin >> f >> s >> c >> r;
 
		ans = max (ans, (ll) d[f-1][s-1][r] * c);
	}
 
	cout << ans;
}
