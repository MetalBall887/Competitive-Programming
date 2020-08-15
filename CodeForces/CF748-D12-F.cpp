#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//The answer is always 1 and the only city lies in the weighted centroid of this graph. That means, if this vertex is a root of the tree, in each its child subtree
//there is at most half of all teams. Now we can write all teams in this tree's dfs order and pair i-th with (i+k)-th and each pair will belong to two different
//subtrees, so the shortest path will go through the weighted centroid.
 
using namespace __gnu_pbds;
 
#define N 1000000
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const int M = 1e6;
 
int n, sz[N], k, b[N];
 
vector <int> g[N], v;
 
int dfs (int x, int p) {
	for (int to : g[x]) {
		if (to == p) continue;
		sz[x] += dfs (to, x);
	}
 
	return sz[x];
}
 
int centroid (int x, int p) {
	for (int to : g[x]) {
		if (to == p) continue;
		if (sz[to] > k) return centroid (to, x);
	}
 
	return x;
}
 
void order (int x, int p) {
	if (b[x]) v.push_back (x);
	for (int to : g[x]) {
		if (to != p) order (to, x);
	}
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
 
	for (int i = 0; i < 2 * k; i++) {
		int a;
		cin >> a;
		sz[a-1]++;
		b[a-1] = 1;
	}
 
	dfs (0, -1);
	int c = centroid (0, -1);
 
	if (b[c]) v.push_back (c);
 
	for (int to : g[c]) {
		order (to, c);
	}
 
	cout << 1 << endl << c + 1 << endl;
 
	for (int i = 0; i < k; i++) {
		cout << v[i] + 1 << ' ' << v[i + k] + 1 << ' ' << c + 1 << '\n';
 	}
}
