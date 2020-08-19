#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//For every vertex x with a value v and its (possibly indirect) child y v will be added to the value of y if the parities of heights are the same and subtracted
//otherwise. If we keep a segment tree where the vertex add the value on the segment corresponding to the subtree if the height of the vertex is even or subtract
//otherwise, then the value on a position in this segment tree will already be an alternating sum of ascendants' values without propagating, but it always starts
//with a +, but it has to be the opposite when the height of the query node is odd.
 
//using namespace __gnu_pbds;
 
#define N 1000000
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const int M = 1e6;
 
int tin[N], tout[N], a[N], n, m, timer;
int h[N];
 
vector <int> g[N];
 
void dfs (int x, int up) {
	if (up != -1) h[x] = h[up] + 1;
	tin[x] = ++timer;
 
	for (int to : g[x])
		if (to != up) dfs (to, x);
 
	tout[x] = timer;
}
 
struct BIT {
	ll t[N];
 
	void update (int x, ll d) {
		for (; x <= n; x = (x | (x + 1)))
			t[x] += d;
	}
 
	ll get (int r) {
		ll sum = 0;
 
		for (; r >= 0; r = (r & (r + 1)) - 1)
			sum += (ll) t[r];
 
		return sum;
	}
 
	ll get (int l, int r) { return get (r) - get (l - 1); }
} t;
 
int main () {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
 
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
 
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
 
		g[a].push_back (b);
		g[b].push_back (a);
	}
 
	dfs (0, -1);
 
	for (int i = 0; i < m; i++) {
		int c, x, val;
 
		cin >> c;
 
		if (c == 1) {
			cin >> x >> val;
			x--;
 
			if (h[x] & 1) val = -val;
 
			t.update (tin[x], val);
			t.update (tout[x] + 1, -val);
 
		} else {
			cin >> x; x--;
			ll ans = t.get (tin[x]);
			if (h[x] & 1) ans = a[x] - ans;
			else ans = a[x] + ans;
 
			cout << ans << '\n';
		}
	}
}
