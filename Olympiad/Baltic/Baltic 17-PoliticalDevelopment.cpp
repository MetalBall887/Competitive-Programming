#include <bits/stdc++.h>
//The claim from statement is, in every subgraph there is a vertex with degree < K. Algorithm is, in an arbitrary subgraph we
//take the vertex with the smallest degree and find all cliques for it and his neighbors in O(2^k). Remove the vertex and 
//check other cliques inductively.
 
#define N 1000001
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int d[N], n, m, k, lg[N], u[N];
int bp[N];
bitset <1050> dp;
 
vector <int> g[N];
 
set < pair <int, int> > s;
 
int find_cl (vector <int> v) {
	sort (v.begin (), v.end ());
	int s = v.size (), gl[v.size ()], mx = 0;
 
	memset (gl, 0, sizeof (gl));
 
	for (int i = 0; i < v.size (); i++) {
		int ptr = 0;
		for (int j = 0; j < v.size (); j++) {
			if (binary_search (g[v[i]].begin(), g[v[i]].end(), v[j])) gl[i] |= (1 << j);
		}
	}
 
	dp.reset ();
	dp[0] = 1;
 
	for (int i = 1; i < (1 << s); i++) {
		int x = (i & -i);
		if (dp[i - x] && ((i - x) & gl[lg[x]]) == (i - x)) {
			dp[i] = 1;
			mx = max (mx, bp[i]);
		}
	}
 
	return mx;
}
 
int main () {
	ios::sync_with_stdio(false);
	cin.tie (NULL);
	cin >> n >> k;
 
	for (int i = 0; i <= k; i++)
		lg[(1 << i)] = i;
 
	for (int i = 1; i < (1 << k); i++) {
		bp[i] = bp[i - (i & -i)] + 1;
	}
 
	for (int i = 0; i < n; i++) {
		cin >> d[i];
		g[i].resize (d[i]);
		for (int j = 0; j < d[i]; j++)
			cin >> g[i][j];
		sort (g[i].begin(), g[i].end());
		s.insert ({d[i], i});
	}
 
	int ans = 0;
 
	while (!s.empty ()) {
		int x = s.begin () -> second;
		u[x] = 1;
		vector <int> v;
 
		v.push_back (x);
 
		for (int to : g[x])
			if (!u[to])
				v.push_back (to);
 
		ans = max (ans, find_cl (v));
		s.erase ({d[x], x});
 
		for (int to : g[x]) {
			if (u[to]) continue;
			s.erase ({d[to], to});
			d[to]--;
			if (d[to]) s.insert ({d[to], to});
		}
	}
 
	cout << ans;
 
	return 0;
}
