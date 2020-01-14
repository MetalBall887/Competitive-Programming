#include <bits/stdc++.h>
using namespace std;
//dp_x[i][j] - the minimum price to buy i itmes from first j children of x, where 0-th children is x itself. dp_x can be computed in 
//O(N^2) by knapsack dp technique. But important is, the whole algorithm will be O(N^2) too. Each pair of vertices will both be 
//descendants of x but in different children subtrees only once - when x is their LCA. So if u1, u2, u3,... are children of x, 
//complexity of calculating dp_x will be O(sz[u1]*sz[u2] + (sz[u1] + sz[u2])*sz[u3] + ...) = O(the number of pairs of vertices for which
//x is the lowest common ancestor). Since for each pair there is only one LCA, the sum of this from all x is the number of pairs.
 
typedef long long ll;
 
const ll N = 1e6, MOD = 1e9 + 7, INF = 1e18;
 
int d[5001][5001][2], n, p[5001], c[5001], b[5001], x;
int sz[5001];
 
vector <int> g[5001];
 
void knapsack (int x) {
	int dp[sz[x] + 1][g[x].size () + 1];
	for (int z = 0; z < 2; z++) {
		for (int i = 0; i <= sz[x]; i++)
			fill (dp[i], dp[i] + g[x].size () + 1, (int)1e9 + 1);
 
		if (!z) dp[0][0] = 0;
		dp[1][0] = c[x] - (z ? b[x] : 0);
 
		int S = 1;
 
		for (int i = 0; i < g[x].size (); i++) {
			int to = g[x][i];
			for (int j = 0; j <= S; j++) {
				for (int k = 0; k <= sz[to]; k++) {
					dp[j+k][i+1] = min (dp[j+k][i+1], dp[j][i] + d[to][k][z]);
					dp[j+k][i+1] = min (dp[j+k][i+1], (int)1e9 + 1);
				}
			}
			S += sz[to];
		}
 
		assert (S == sz[x]);
 
		for (int i = 0; i <= sz[x]; i++) {
			d[x][i][z] = dp[i][g[x].size ()];
		}
	}
 
	for (int i = 0; i <= sz[x]; i++) {
		d[x][i][1] = min (d[x][i][1], d[x][i][0]);
	}
}
 
int dfs (int x) {
	sz[x] = 1;
 
	for (int to : g[x])
		sz[x] += dfs (to);
 
	knapsack (x);
	return sz[x];
}
 
int main () {
	cin >> n >> x;
 
	for (int i = 0; i < n; i++) {
		int p;
		cin >> c[i] >> b[i];
		if (i) {
			cin >> p;
			g[p-1].push_back (i);
		}
	}
 
	dfs (0);
 
	int y = 0;
 
	while (y <= n && d[0][y][1] <= x) {
		y++;
	}
	cout << y - 1;
}
