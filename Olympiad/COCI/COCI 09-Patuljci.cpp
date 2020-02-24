#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//A significant property of segments with dominating elements is, if we divide it into two parts of arbitrary length, in at least one of
//the parts there will be the same domingating element. That means, we can use a D&C method if we will be able to check if an element
//dominates sime segments. For that we have to count the number of occurences of this element in this segment, which is done by binary 
//search on the record of occurences of this element. 

using namespace __gnu_pbds;

#define N 1000001

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int a[N], n, start, m;

vector <int> g[N];

int ub (vector <int>& v, int x) {
	return upper_bound (v.begin(), v.end(), x) - v.begin ();
}

int lb (vector <int>& v, int x) {
	return lower_bound (v.begin(), v.end(), x) - v.begin ();
}

struct SegTree {
	int t[2 * N];
	int merge (int a, int b, int l, int r) {
		int sz_a = (a != -1 ? ub (g[a], r) - lb (g[a], l) : 0); 
		int sz_b = (b != -1 ? ub (g[b], r) - lb (g[b], l) : 0);
		if (2 * sz_a > r - l + 1) return a;
		if (2 * sz_b > r - l + 1) return b;
		return -1;
	}

	int build (int node, int tl, int tr) {
		if (tl == tr) return t[node] = (tl < n ? a[tl] : -1);
		else {
			int tm = (tl + tr) / 2;
			t[node] = merge (build (2 * node, tl, tm), build (2 * node + 1, tm + 1, tr), tl, tr);
			return t[node];
		}
	}

	int get (int node, int tl, int tr, int l, int r) {
		if (tr < l || r < tl) return -1;
		if (l <= tl && tr <= r) return t[node];
		int tm = (tl + tr) / 2;
		return merge (get (2 * node, tl, tm, l, r), get (2 * node + 1, tm + 1, tr, l, r), max (tl, l), min (tr, r));
	}
} t;

int main () {
	ios::sync_with_stdio (0);
	cin.tie (NULL);
	cin >> n >> m;
	start = 1;
	while (start < n) start <<= 1;

	for (int i = 0; i < n; i++) {
		cin >> a[i];
		g[a[i]].push_back (i);
	}

	t.build (1, 0, start - 1);
	cin >> m;

	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		int x = t.get (1, 0, start - 1, a, b);
		if (x == -1) cout << "no\n";
		else cout << "yes " << x << '\n';
	}
}
