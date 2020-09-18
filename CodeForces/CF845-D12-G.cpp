#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//Note that if we allow multiedges, the path will be an eulerian graph. If we delete all double edges (since they don't contribute to xor), there won't be any
//multiedges but the graph won't be connected anymore. For subgraphs of a connected graph G with even degrees there is a vector space, where sum is exclusive 
//union of edges (note that weight of the sum of the graphs is the xor of sums of graphs). Now for asuch vector space take a spanning tree and for each edge not
//in the tree add it to the tree and a cycle obtained will be a basic cycle. Now for such any path can be generated with path 1-n and any combination of basic
//cycles. Now we want to take a combination of cycles such that the xor of these combination and the path is minimal. For that treat the numbers we need to xor
//as vectors and apply gaussian elimination.
 
//using namespace __gnu_pbds;
 
#define N 2000001
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
vector < pair <int, int> > g[N];
 
vector <int> v;
 
int n, m, d[N], u[N];
 
void dfs (int x, int p) {
	u[x] = 1;
	for (auto [to, w] : g[x]) {
		if (u[to] && to != p) {
			v.push_back (d[to] ^ d[x] ^ w);
		}
		else if (!u[to]) {
			d[to] = w ^ d[x];
			dfs (to, x);
		}
	}
}
 
int main () {
	cin >> n >> m;
 
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;
 
		g[u].push_back ({v, w});
		g[v].push_back ({u, w});
	}
 
	dfs (0, -1);
 
	int ptr = 0;
 
	for (int i = 30; i >= 0; i--) {
		int j = ptr + 1;
		while (j < v.size ()) {
			if (v[j] & (1 << i)) break;
			j++;
		}
 
		if (j == v.size ()) continue;
		ptr++;
		swap (v[j], v[ptr]);
 
		for (int j = ptr + 1; j < v.size (); j++)
			if (v[j] & (1 << i)) v[j] ^= v[ptr];
	}
 
	int ans = d[n-1];
 
	for (int i = 0; i < v.size (); i++) {
		if (ans > (ans ^ v[i])) ans ^= v[i];
	}
 
	cout << ans << endl;
}
