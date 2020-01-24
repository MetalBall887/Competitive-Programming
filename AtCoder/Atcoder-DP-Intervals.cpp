#include <bits/stdc++.h>
 
#define N 1000000
//d[i] - the maximal score obtained if the last 1 was put in position i. In this position we are looking for the optimal place
//for our second last 1 d[j] + (sc_i = the sum of scores of all segments that appear in position i) - (sc_ij = the sum of
//scores of all segments going through both i and j to avoid double-counting). di = sc_i + max(dj + sc_ij for all 0 <= j < i).
//We can contain dj + sc_ij by keeping all segments going through i in a segment tree, where there are only values d[i] and 
//adding/removing them from it, by range updates. Finding maximal in prefix can be done by the same segment tree
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e18;
 
struct LazySeg {
	ll t[N], t_add[N], start;
 
	void push (int node) {
		t[node] += t_add[node];
		if (node < start) {
			t_add[2 * node] += t_add[node];
			t_add[2 * node + 1] += t_add[node];
		}
		t_add[node] = 0;
	}
 
	void build (int n) {
		start = 1;
		while (start < n) start <<= 1;
	}
 
	void update (int node, int tl, int tr, int l, int r, ll d) {
		push (node);
		if (r < tl || tr < l) return;
		if (l <= tl && tr <= r) {
			t_add[node] += d;
			push (node);
			return;
		}
 
		int tm = (tl + tr) / 2;
		update (2 * node, tl, tm, l, r, d);
		update (2 * node + 1, tm + 1, tr, l, r, d);
		t[node] = max (t[2 * node], t[2 * node + 1]);
	}
 
	ll get (int node, int tl, int tr, int l, int r) {
		if (r < l) return -INF;
		push (node);
		if (tr < l || r < tl) return -INF;
		if (l <= tl && tr <= r) return t[node];
 
		int tm = (tl + tr) / 2;
		return max (get (2 * node, tl, tm, l, r), get (2 * node + 1, tm + 1, tr, l, r));
	}
} d;
 
ll n, m, sum, ans;
 
struct seg {
	ll l, r, a;
 
	bool operator < (const seg& b) const {
		if (l == b.l) return r < b.r;
		return l < b.l;
	}
} a[N];
 
set < pair <int, int> > s;
 
int main () {
	cin >> n >> m;
 
	for (int i = 0; i < m; i++) {
		cin >> a[i].l >> a[i].r >> a[i].a;
		a[i].l--, a[i].r--;
	}
 
	d.build (n);
 
	sort (a, a + m);
	int ptr = 0;
 
	for (int i = 0; i < n; i++) {
		ll x;
		while (ptr < m && a[ptr].l == i) {
			sum += a[ptr].a;
			s.insert ({a[ptr].r, ptr});
			d.update (1, 0, d.start - 1, a[ptr].l, a[ptr].r, -a[ptr].a);
			ptr++;
		}
 
		x = max (0LL, d.get (1, 0, d.start - 1, 0, i - 1)) + sum;
		ans = max (x, ans);
		d.update (1, 0, d.start - 1, i, i, x);
 
		while (!s.empty () && s.begin () -> first <= i) {
			int p = s.begin () -> second;
			d.update (1, 0, d.start - 1, a[p].l, a[p].r, a[p].a);
			sum -= a[p].a;
			s.erase (s.begin ());
		}
	}
 
	cout << ans << endl;
}
