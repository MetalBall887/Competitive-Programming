#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Let's look at this game in such way: we move from level 1 to k and on each level we choose a vertex and delete the subtree
//rooted in this vertex. If at level k after removal there still are vertices, we lost. Now let's for a vertex v on fixed level
//l denote the smallest level where the subtree rooted in this vertex "branches" (i.e. there is a vertex with degree > 2)
//as f(v) and the number of vertices not above the level l as n. The strategy is on each level to remove the vertex with minimal 
//f(v). At some point minimal f(v) will be 0, let's say d moves passed. Now from level l's point of view, d subtrees will be 
//deleted, each of deleted subtrees had f(v) <= d, so the sizes of each of them were at least d + 2(k - l - d), so for level
//l + d: n' <= n - d(d + 2(k - l - d)) = n-d(2(k-l)-d). Let's state that if (k-l)^2>=n, we can win. For l = k it's obvious, 
//for other l let's assume (k-l)^2>=n and find d as stated above: n' <= n - d(2(k-l)-d) <= (k-l)^2 - 2d(k-l) + d^2 = (k-(l+d))^2.
//That means, from any level if n^2 <= (k-l)^2, we can find make such d moves, that next state will also fulfill this condition.
//And once we'll inevitably end up at l = k with the same invariant fullfilled. Thus, if k^2 >= n, it's always possible. 
//If k^2 < n, then k < 20 and we can do the bitmask dp d[i][j] - is there a way to cover first i vertices of depth k where
//j is a bitmask of levels where we marked a node.

using namespace __gnu_pbds;
 
#define N 1000003
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int n, k, ptr;
bitset <1 << 21> d[401];
 
vector <int> g[N];
vector < pair <int, int> > v[401];
 
void dfs (int x, int p, int h) {
	if (h == k) {
		v[++ptr].push_back ({ptr, h - 1});
		return;
	}
 
	int l = ptr + 1;
 
	for (int to : g[x])
		if (to != p) dfs (to, x, h + 1);
	int r = ptr;
	if (h && l) v[r].push_back ({l, h - 1});
}
 
int main () {
	cin >> n >> k;
 
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		g[a].push_back (b);
		g[b].push_back (a);
	}
 
	if (k * k >= n) {
		cout << "DA";
		return 0;
	}
 
	dfs (0, -1, 0);
 
	d[0][0] = 1;
	for (int i = 1; i <= ptr; i++) {
		for (int j = 1; j < (1 << k); j++) {
			for (auto a : v[i]) {
				if (j & (1 << a.second)) {
					d[i][j] = (d[i][j] | d[a.first - 1][j - (1 << a.second)]);
				}
			}
 
			if (ptr == i && d[i][j]) {
				cout << "DA";
				return 0;
			}
		}
	}
 
	cout << "NE";
}
