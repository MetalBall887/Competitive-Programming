#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//The straightforward MST works in O(n^2) but we can reduce the edges from i-th vertex to the vertices with the closest values to some multiple of p[i] (excluding
// p[i] itself). It can be shown that this set of edges is sufficient to contain a minimal spanning tree in it: just prove that every edge from the original graph
//can be substituted with a path in a reduced graph with the same weight, so we can replace this edge with a path that lies completely in a reduced graph.
//If we do not repeat searches for the same p[i], we get O(MaxPlogMaxP) edges. With Kruskal and counting sort this will be the asymptotic complexity of the solution.
using namespace __gnu_pbds;
 
using namespace std;
 
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
 
const ll N = 2000001;
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const int maxa = (int)1e7 + 1;
int a[N], n;

int p[N], sz[N], e[maxa + 1], u[maxa + 1];

vector<pair<int, int>> v[maxa + 1];

int f(int i, int j) {
	if (a[i] > a[j]) swap(i, j);
	return a[j] % a[i];
}

int find(int x) {
	if (p[x] == x) return x;
	return p[x] = find(p[x]);
}

bool unite(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return false;

	if (sz[a] < sz[b]) swap(a, b);

	sz[a] += sz[b];
	p[b] = a;

	return true;
}

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;

	fill(e, e + maxa + 1, -1);
	fill(u, u + maxa + 1, -1);

	for (int i = 0; i < n; i++) {
		sz[i] = 1, p[i] = i;
	}

	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	sort(a, a + n);

	for (int i = 0; i < n; i++) {
		e[a[i]] = i;
	}


	for (int i = maxa - 1; i >= 0; i--) {
		if (e[i] == -1) e[i] = e[i+1];
	}

	for (int i = 0; i < n; i++) {

		if (e[a[i] + 1] != -1) v[f(i, e[a[i] + 1])].push_back({i, e[a[i] + 1]});

		if (u[a[i]] != -1) {
			v[0].push_back({u[a[i]], i});
			continue;
		}

		u[a[i]] = i;

		for (int k = 2 * a[i]; k < maxa; k += a[i]) {
			u[k] = i;
			if (e[k] != -1 && a[e[k]] <= k + a[i]) {
				v[a[e[k]] - k].push_back({i, e[k]});
			}
		}
	}

	ll ans = 0;

	for (int i = 0; i <= maxa; i++) {
		for (auto& x : v[i]) {
			if (unite(x.first, x.second)) ans += i;
		}	
	}

	cout << ans;

}
