#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//For a version without walls we can construct a bipartite graph where one part is for rows and the left part is for columns
//and there is an edge (i, j) if the cell (i, j) is free. The solution is a maximum bipartite matching. For walls we can see
//that people in one row still don't have to see each other as they can be divided by a wall. Let's divide each row and each
//column in segments by these walls. If and only if two soldiers are in the same row or column segment they'll see each other.
//It leaves us with potentially O(nm) vertices and O(nm) edges, so kuhn's algorithm will work in O(n^2m^2) but kuhn works fast
//with sparse graphs, so it's enough for solution to pass. For a better complexity Dinic's algorithm might be a good choice
 
using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int d[200][200], n, m, ptr, ptr2;
int x[200][200], a[200][200];
vector <int> u, g[N], p;

map < pair <int, int>, pair <int, int> > edge;

bool kuhn (int x) {
	if (u[x]) return false;
	u[x] = 1;

	for (int to : g[x]) {
		if (p[to] == -1 || kuhn (p[to])) {
			p[to] = x;
			return true;
		}
	}

	return false;
}

int main () {
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> a[i][j];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (a[i][j] == 2) ptr++;
			x[i][j] = ptr;
		}
		ptr++;
	}

	for (int j = 0; j < m; j++) {
		for (int i = 0; i < n; i++) {
			if (a[i][j] == 2) ptr2++;
			if (!a[i][j]) {
				edge[{x[i][j], ptr2}] = {i, j};
				g[x[i][j]].push_back (ptr2);
			}
		}
		ptr2++;
	}

	p.resize (ptr2);
	u.resize (ptr);

	int ans = 0;

	fill (p.begin(), p.end(), -1);

	for (int i = 0; i < ptr; i++) {
		fill(u.begin(), u.end(), 0);
		ans += kuhn (i);
	}

	cout << ans << '\n';

	for (int i = 0; i < ptr2; i++) {
		if (p[i] != -1) {
			auto x = edge[{p[i], i}];
			cout << x.first + 1 << ' ' << x.second + 1 << '\n';
		}
	}
}
