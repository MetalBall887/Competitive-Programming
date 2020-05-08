#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//First of all, let's make several transformations: profit <= money/length => money - profit*length >= 0. That means, we can
//check if profit is smaller than some x if for each edge of length l give a cost -l*x. A deal between two cities will be 
//(the biggest sell/buy difference for towns between cities or 0) - (the cost of the shortest path). If there is a 
//non-negative cycle in a graph where vertices are cities and edges are deals, that means that is a cycle, profit of which is
//at least x. We can find the maximum length cycle with floyd-warshall and do a binary search on profits.
 
using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
ll un_dist[200][200], deal[200][200];
ll sell[200][2000], buy[200][2000], n, m, k;
ll d[200][200];
 
bool check (ll x) {
 
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (un_dist[i][j] == INF) d[i][j] = -INF;
			else {
				d[i][j] = deal[i][j] - x * un_dist[i][j];
			}
			d[i][j] = max (d[i][j], -INF);
		}
 
 
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (d[i][j] < d[i][k] + d[k][j]) d[i][j] = d[i][k] + d[k][j];
 
	for (int i = 0; i < n; i++)
		if (d[i][i] >= 0) return true;
	if (!x) return true;
 
	return false;
}
 
int main () {
	cin >> n >> m >> k;
 
	for (int i = 0; i < n; i++)
		for (int j = 0; j < k; j++) {
			cin >> buy[i][j] >> sell[i][j];
		}
 
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int it = 0; it < k; it++) {
				if (sell[j][it] == -1 || buy[i][it] == -1) continue;
				deal[i][j] = max (deal[i][j], sell[j][it] - buy[i][it]);
			}
 
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			un_dist[i][j] = INF;
 
	for (int i = 0; i < m; i++) {
		ll u, v, l;
		cin >> u >> v >> l;
		u--, v--;
		un_dist[u][v] = l;
	}
 
	for (int k = 0; k < n; k++) 
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				un_dist[i][j] = min (un_dist[i][j], un_dist[i][k] + un_dist[k][j]);
 
	ll l = 0, r = 1e9 + 10;
 
	while (l < r) {
		ll mid = (l + r + 1) / 2;
		if (check (mid)) l = mid;
		else r = mid - 1;
	}
 
	cout << l << endl;
}
