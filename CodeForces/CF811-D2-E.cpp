#include <bits/stdc++.h>
//We can apply Divide and Conquer solution here. Let's build a segment tree on this flag. The one
//thing to do is to learn how to merge subflags in reasonable time. We don't need to know the whole
//subflag, ideally only the number of components completely inside the flag (components that can't be
//changed after merging) and components appearing on the edges of the flag. Only those that touch in the
//inner sides of two subflags can be merged into one, which leaves us with O(n) components merging during
//the subflags merge. We can figure out which ones to merge by running a search on a graph or DSU

typedef long long ll;
 
const ll N = 1e6;
 
using namespace std;

int n, a[10][N], m, q;

struct state {
	int l, r, num;
	bool nl;
	vector <int> pl, pr;

	state () : nl (true) {}

	state (int x) : l (x), r (x) {
		pl.resize (n);
		pr.resize (n);
		pl[0] = pr[0] = 1;
		for (int i = 1; i < n; i++) {
			pl[i] = pl[i-1];
			if (a[i-1][x] != a[i][x]) pl[i]++;
			pr[i] = pl[i];
		}

		num = pl[n-1];
		nl = false;
	}

	state (int l, int r, vector <int> pl, vector <int> pr, int num) 
		: l (l), r (r), pl (pl), pr (pr), num (num) {
		nl = false;
	}
};

state merge (state x, state y) {
	if (x.nl) return y;
	if (y.nl) return x;
	int p[50], sz[50], nm = x.num + y.num, s[50] = {0,};

	for (int i = 0; i <= 4 * n; i++) {
		p[i] = i, sz[i] = 1;
	}

	for (int i = 0; i < n; i++) {
		if (a[i][x.r] == a[i][y.l]) {
			int a = x.pr[i], b = 2 * n + y.pl[i];
			while (a != p[a]) a = p[a];
			while (b != p[b]) b = p[b];

			if (a == b) continue;
			nm--;
			if (sz[a] < sz[b]) swap (a, b);
			sz[a] += sz[b];
			p[b] = a;
		}
	}

	for (int i = 0; i < n; i++) {
		y.pr[i] += 2 * n;
		
		while (p[x.pl[i]] != x.pl[i]) x.pl[i] = p[x.pl[i]];
		while (p[y.pr[i]] != y.pr[i]) y.pr[i] = p[y.pr[i]];
	}

	state st (x.l, y.r, x.pl, y.pr, nm);

	for (int i = 0; i < n; i++) {
		s[st.pl[i]] = 1;
		s[st.pr[i]] = 1;
	}

	int n_ptr = 0;

	for (int i = 0; i <= 4 * n; i++) {
		if (s[i]) s[i] = ++n_ptr;
	}

	for (int i = 0; i < n; i++) {
		st.pl[i] = s[st.pl[i]];
		st.pr[i] = s[st.pr[i]];
	}

	return st;
}

struct SegTree {
	state t[4 * N];
	int start;

	void build (int n) {
		start = 1;
		while (start < n) start <<= 1;

		for (int i = 0; i < n; i++) {
			t[start + i] = i;
		}

		for (int i = start - 1; i > 0; i--) {
			t[i] = merge (t[2 * i], t[2 * i + 1]);
		}
	}

	state get (int node, int tl, int tr, int l, int r) {
		if (tr < l || r < tl) return state ();

		if (l <= tl && tr <= r) return t[node];
		int tm = (tl + tr) / 2;
		return merge (get (2 * node, tl, tm, l, r), get (2 * node + 1, tm + 1, tr, l, r));
	}
} t;

int main () {
	ios::sync_with_stdio (0);
	cin.tie (NULL);
	cin >> n >> m >> q;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
		}
	}

	t.build (m);

	for (int i = 0; i < q; i++) {
		int l, r;
		cin >> l >> r;

		auto a = t.get (1, 0, t.start - 1, l - 1, r - 1);

		/*for (int i = 0; i < n; i++) {
			cout << a.pl[i] << ' ' << a.pr[i] << endl;
		}
		cout << "------------------\n";*/
		cout << a.num << '\n';
	}
}
