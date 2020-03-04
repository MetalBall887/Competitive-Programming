#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Solved it with 2d nested segment trees with range update. In each node of SegTree2D there is an "orthogonal" segment tree for each y
//on this range maintaining the maximum on [left x of the range, right x of the range] in row y. For range updates on x we could have 
//implemented lazy propagation but note that, since values in cells only grow, we don't need to deal with the order of range updates 
//in ta segment tree as the newest one will also be the biggest one.

using namespace __gnu_pbds;

#define N 1000001

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

struct SegTree {
	vector <int> t, ta;
	int start;

	void push (int node) {
		t[node] = max (t[node], ta[node]);

		if (node < start) {
			ta[2 * node] = max (ta[2 * node], ta[node]);
			ta[2 * node + 1] = max (ta[2 * node + 1], ta[node]);
		}

		ta[node] = 0;
	}

	void build (int n) {
		start = 1;
		while (start < n) start <<= 1;
		t.resize (2 * start), ta.resize (2 * start);
	}

	void update (int node, int tl, int tr, int l, int r, int d) {
		push (node);
		if (r < tl || tr < l) return;

		if (l <= tl && tr <= r) {
			ta[node] = max (ta[node], d);
			push (node);
			return;
		}

		int tm = (tl + tr) / 2;

		update (2 * node, tl, tm, l, r, d);
		update (2 * node + 1, tm + 1, tr, l, r, d);

		t[node] = max (t[2 * node], t[2 * node + 1]);
	}

	int get (int node, int tl, int tr, int l, int r) {
		push (node);
		if (r < tl || tr < l) return 0;

		if (l <= tl && tr <= r) {
			return t[node];
		}

		int tm = (tl + tr) / 2;

		int ans = max (get (2 * node, tl, tm, l, r), get (2 * node + 1, tm + 1, tr, l, r));
		return ans;
	}

	int get (int l, int r) {
		return get (1, 0, start - 1, l, r);
	}

	void update (int l, int r, int d) {
		update (1, 0, start - 1, l, r, d);
	}
};

struct SegTree2D {
	vector<SegTree> t, ta;
	int start;

	void build (int n, int m) {
		start = 1;
		while (start < n) start <<= 1;

		t.resize (2 * start), ta.resize (2 * start);
		for (int i = 0; i < 2 * start; i++) {
			t[i].build (m), ta[i].build (m);
		}
	}

	void update (int node, int tl, int tr, int lx, int rx, int ly, int ry, int d) {
		if (rx < tl || tr < lx) return;

		if (lx <= tl && tr <= rx) {
			ta[node].update (ly, ry, d);
			t[node].update (ly, ry, d);

			return;
		}

		int tm = (tl + tr) / 2;

		update (2 * node, tl, tm, lx, rx, ly, ry, d);
		update (2 * node + 1, tm + 1, tr, lx, rx, ly, ry, d);

		t[node].update (ly, ry, d);
	}

	int get (int node, int tl, int tr, int lx, int rx, int ly, int ry) {
		if (rx < tl || tr < lx) return 0;

		if (lx <= tl && tr <= rx) {
			return max (t[node].get (ly, ry), ta[node].get (ly, ry));
		}

		int tm = (tl + tr) / 2;

		int ans = max (get (2 * node, tl, tm, lx, rx, ly, ry), get (2 * node + 1, tm + 1, tr, lx, rx, ly, ry));
		return max (ans, ta[node].get (ly, ry));
	}

	int get (int lx, int rx, int ly, int ry) {
		return get (1, 0, start - 1, lx, rx, ly, ry);
	}

	void update (int lx, int rx, int ly, int ry, int d) {
		update (1, 0, start - 1, lx, rx, ly, ry, d);
	}
} t;

int D, S, n;

int main () {
	cin >> D >> S;

	t.build (D, S);

	cin >> n;

	int ans = 0;

	for (int i = 0; i < n; i++) {
		int d, s, w, x, y;

		cin >> d >> s >> w >> x >> y;

		int mx = t.get (x, x + d - 1, y, y + s - 1);
		t.update (x, x + d - 1, y, y + s - 1, mx + w);
		ans = max (ans, mx + w);
	}

	cout << ans;
}
