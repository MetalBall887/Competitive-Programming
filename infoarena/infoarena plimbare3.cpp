#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <set>
#include <cstring>
//The longest parh for a moving edge is got like this: take both subtrees our original tree divides to by removing that edge,
//find diameters of both subtrees, connect their ends with the moving edge. So if we walk by the tree with dfs, we should
//keep diameter of the subtree and diameter of the whole tree without this subtree for each edge. Finding diameter of the
//subtree rooted in x is easier: find two longest paths starting from x and starting from different edges. If diameter
//goes through x, those paths combined will be diameter. If not, then it goes through some of x's children, so just proceed
//with this dp. Finding for each edge (u, v) diameter for a tree without subtree rooted in v can be done by taking the
//longest paths from v down to any leaves not going through (u, v) and longest path up through his parent. Taking two 
//biggest values out of these will form a diameter.
#include <assert.h>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;

ifstream fin ("plimbare3.in");
ofstream fout ("plimbare3.out");
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int n, dp[2][200000], di[200000], ans[200000];

vector < pair <int, int> > g[200000];

void merge (int& mx, int& sec, int a) {
	if (mx <= a) {
		sec = mx;
		mx = a;
	}
	else sec = max (sec, a);
}

void dp_dfs (int x, int p) {
	for (auto f : g[x]) 
		if (f.first != p) {
		int to = f.first;
		dp_dfs (to, x);
		
		if (dp[0][x] <= dp[0][to] + 1) {
			dp[1][x] = dp[0][x];
			dp[0][x] = dp[0][to] + 1;
		}
		else dp[1][x] = max (dp[1][x], dp[0][to] + 1);

		di[x] = max (di[to], di[x]);
	}
	di[x] = max (di[x], dp[0][x] + dp[1][x]);
}

void dfs (int x, int p, int mx, int di_up) {
	if (g[x].empty ()) return;

	pair <int, int> diam[2], dist[3];

	for (int i = 0; i < g[x].size (); i++) {
		int to = g[x][i].first;
		if (to == p) continue;
		pair <int, int> cur_diam = {di[to], to}, cur_dist = {dp[0][to] + 1, to};

		if (cur_diam >= diam[0]) {
			diam[1] = diam[0];
			diam[0] = cur_diam;
		}
		else diam[1] = max (diam[1], cur_diam);

		if (cur_dist >= dist[0]) {
			dist[2] = dist[1];
			dist[1] = dist[0];
			dist[0] = cur_dist;
		}
		else if (cur_dist >= dist[1]) {
			dist[2] = dist[1];
			dist[1] = cur_dist;
		}
		else dist[2] = max (dist[2], cur_dist);

	}

	for (int i = 0; i < g[x].size (); i++) {
		int to = g[x][i].first;
		if (to == p) continue;

		int cur_d, cur[2];

		if (to == diam[0].second) cur_d = diam[1].first;
		else cur_d = diam[0].first;

		if (to == dist[0].second){
			cur[0] = dist[1].first;
			cur[1] = dist[2].first;
		} 
		else if (to == dist[1].second) {
			cur[0] = dist[0].first;
			cur[1] = dist[2].first;
		}
		else {
			cur[0] = dist[0].first;
			cur[1] = dist[1].first;
		}


		int best_diam = max (di_up, max (max (mx, cur[1]) + cur[0], cur_d));

		ans[g[x][i].second] = 1 + di[to] + best_diam;
		dfs (to, x, max (mx + 1, cur[0] + 1), best_diam);
	}
}
 
int main () {

	fin >> n;

	for (int i = 0; i < n - 1; i++) {
		int u, v;

		fin >> u >> v;

		g[u-1].emplace_back (v - 1, i);
		g[v-1].emplace_back (u - 1, i);
	}

	dp_dfs (0, -1);
	dfs (0, -1, 0, 0);

	for (int i = 0; i < n - 1; i++)
		fout << ans[i] << '\n';
}
