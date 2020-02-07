#include <bits/stdc++.h>
//Until there are vertices with odd degrees, eliminate them by connecting pairs of them with edges (there is an even number
//of such vertices). After that, we can build an eulerian cycle on this graph. By traversing this cycle we can orient edges
//in pattern x <- x -> x <- x -> x... If the number of edges is even, this pattern will not be ruined by connecting the last
//edge in the cycle. If the number of edges is odd, than it's not possible to orient edges the right way, because the number
//of edges = the sum of in-degrees is odd, which can't happen if all in-degrees are even. Not to ruin the euleriantiy of the
//graph, we add a loop. Now, for each occurence of any vertex we can see that it's either -> x <- or <- x ->, so it will always
//add 2 do out-degree or in-degree.
 
#define N 1000001
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

ll banned[N], n, m, ptr, a, b;
vector <pair <int, int>> g[N];
vector <int> ans;

void dfs (int x) {
	vector <int> cycle;
	ans.push_back (x);

	bool b = true;

	while (b) {
		b = false;
		while (!g[x].empty ()) {
			auto e = g[x].back ();
			g[x].pop_back ();
			if (!banned[e.second]) {
				x = e.first;
				banned[e.second] = 1;
				cycle.push_back (x);
				b = true;
				break;
			}
		}
	}

	for (int a : cycle) {
		dfs (a);
	}
}

int main () {
	freopen ("ratway.in", "r", stdin);
	freopen ("ratway.out", "w", stdout);
	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		g[a-1].push_back ({b - 1, ++ptr});
		g[b-1].push_back ({a - 1, ptr});
	}

	vector<int> v;

	for (int i = 0; i < n; i++) {
		if (g[i].size () % 2) v.push_back (i);
	}

	for (int i = 0; i < v.size (); i += 2) {
		g[v[i]].push_back ({v[i+1], ++ptr});
		g[v[i+1]].push_back ({v[i], ptr});
	}

	dfs (0);

	vector <pair <int, int>> e;

	for (int i = 0; i < ans.size () - 1; i++) {
		if (i & 1) e.push_back ({ans[i], ans[i+1]});
		else e.push_back ({ans[i+1], ans[i]});
	}

	if (e.size () & 1) e.push_back ({0, 0});

	cout << endl;
	cout << e.size () << '\n';

	for (auto p : e) {
		cout << p.first + 1 << ' ' << p.second + 1 << '\n';
	}
}
