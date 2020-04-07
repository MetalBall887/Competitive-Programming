#include <bits/stdc++.h>
//Construct a graph such that for segment [(i-1)M; iM-1] i there is an edge (i, n + j) for each "excessive" box of product
//j in the segment and instead an edge (n + j, i) if there is no box of product j in segment i. Now we can see that the optimal
//sort is done by the eulerian cycle of this graph.
 
#define N 1000003
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int n, m;
vector <int> a[500][500];
 
vector <int> e;
vector < pair <int, int> > g[1000], ans;
 
void dfs (int x) {
	while (g[x].size ()) {
		auto a = g[x].back ();
		g[x].pop_back ();
		dfs (a.first);
		if (a.second >= 0) e.push_back (a.second);
	}
}
 
int main () {
	cin >> n >> m;
 
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int x;
			cin >> x;
			a[i][x - 1].push_back (i * m + j);
		}
	}
 
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < (int) a[i][j].size () - 1; k++) {
				g[i].push_back ({n + j, a[i][j][k]});
			}
 
			if (a[i][j].empty ()) g[n + j].push_back ({i, -1});
		}
	}
 
	for (int i = 0; i < n + m; i++) {
		dfs (i);
 
		if (e.size ()) {
			ans.push_back ({e[0], n * m});
			for (int k = 0; k < (int) e.size () - 1; k++) {
				ans.push_back ({e[k+1], e[k]});
			}
			ans.push_back ({n * m, e.back ()});
		}
		e.clear ();
	}
	cout << ans.size () << endl;
	for (auto a : ans) {
		cout << a.first + 1 << ' ' << a.second + 1 << '\n';
	}
}
