#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
//dp[i][j][l] - the cost of the subtree rooted in i, if there are j sawmills inside this subtree and the next sawmill will be
//l edges above the root. From this l we can uniquely determine the cost of cutting logs we push from the root. The small 
//note is that in my version j doesn't include sawmill we put into rooting village. So our task is to distribute sawmills
// between direct children, so that the sum of corresponding costs is minimal. We  can do this 
//through 2d helping dp d[i][j] - the best result of assigning i sawmills to first j direct children of our current root.
//the needed assignment result is in the last cell of d. The answer to the problem is in dp[0][k][0].
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e15, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

ll dp[102][102][51], k, n, depth[102][102], w[102], root;

vector <int> g[102];

void process (int v, int l) {

	if (!g[v].size ()) {
		for (int i = 0; i <= k; i++)
			dp[v][l][i] = w[v] * depth[v][l];
		return;
	}

	vector <ll> d[51];

	for (int i = 0; i <= k; i++)
		d[i].resize (g[v].size ());

	for (int i = 0; i <= k; i++) {
		d[i][0] = dp[g[v][0]][l + 1][i];
		if (i) d[i][0] = min (d[i][0], dp[g[v][0]][0][i-1]);
	}

	for (int j = 1; j < g[v].size (); j++) {
		int to = g[v][j];

		for (int i = 0; i <= k; i++) {
			d[i][j] = INF;

			for (int f = 0; f <= i; f++) {
				d[i][j] = min (d[i][j], dp[to][l + 1][f] + d[i - f][j - 1]);
				if (f) d[i][j] = min (d[i][j], dp[to][0][f - 1] + d[i - f][j - 1]);
			}
		}
	}

	for (int i = 0; i <= k; i++) {
		dp[v][l][i] = d[i][g[v].size () - 1] + w[v] * depth[v][l];
	}
}

void dfs (int v, int p) {

	if (v != root) {
		for (int i = 2; i <= n; i++)
			depth[v][i] = depth[p][i-1] + depth[v][1];
	}

	for (int to : g[v])
		if (to != p) {
			dfs (to, v);
		}

	for (int i = 0; i <= n; i++) {
		process (v, i);
	}
}

int main () {
	cin >> n >> k;

	for (int i = 1; i <= n; i++) {
		int v, d;

		cin >> w[i] >> v >> d;

		g[v].push_back (i);
		depth[i][1] = d;
	}

	n++;

	dfs (0, -1);

	cout << dp[0][0][k];
}
