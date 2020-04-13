#include <bits/stdc++.h>
//So it's possible to assign skis to every student if and only if the number of students having shoe sizes [i; j] is at most
//the number of shoes of sizes [i;j+d]. The "only if" part is not hard and the "if" part is proved by proving that in each
//scenario, where there is someone without shoes (let his shoe size be i), and j is the smallest number, such that all shoes
//from the segment [j;i+d] are taken, the interval [i;j] will not have enough shoes. But also this can be proved by Hall's
//theorem, where there is a bipartite graph of students and shoes and there is an edge (a, b) if the student a can wear a shoe
//b. This graph has a bipartite matching <=> for each set of students V let W be the set of shoes at least one of them can use
//then |V| <= |W|. Now let's prove that if there is such V and W |V| > |W|, there is |V'| > |W'| where V' is an interval. 
//1) If W is a union of disjointed segments, there is a segment W', for which there is U - a subset of V corresponding to 
//this segment and will satisfy |U| > |W'|
//2) For W' let V' be the set of students for which only the shoes from W' will fit. U is a subset of V' (actually, U = 
//V'^V), so |V'| >= |U| > |W'|. Also, V' is an interval.
//The rest part is using the fact that the number of shoes is static and quickly finding minimal subsegment with segment trees.
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

ll n, m, k, d;

struct SegTree {
	struct Node {
		ll sum, suf, pref, seg;
		Node () : sum (0), suf (0), pref (0), seg (0) {}
		Node (ll x) : sum (x), suf (x), pref (x), seg (x) {}
	};

	vector <Node> t;

	Node merge (Node a, Node b) {
		Node c;
		c.sum = a.sum + b.sum;
		c.suf = max (b.suf, b.sum + a.suf);
		c.pref = max (a.pref, a.sum + b.pref);
		c.seg = max (a.suf + b.pref, max (a.seg, b.seg));

		return c;
	}

	int start;

	void build (int n) {
		start = 1;
		while (start < n) start <<= 1;

		t.resize (2 * start);

		for (int i = 0; i < n; i++) {
			t[i + start] = Node (-k);
		}

		for (int i = start - 1; i > 0; i--) {
			t[i] = merge (t[2 * i], t[2 * i + 1]);
		}
	}

	void update (int x, ll d) {
		x += start;
		t[x] = Node (t[x].sum + d);

		x >>= 1;

		while (x) {
			t[x] = merge (t[2 * x], t[2 * x + 1]);
			x /= 2;
		}
	}

	Node get (int node, int tl, int tr, int l, int r) {
		if (r < tl || tr < l) return Node ();
		if (l <= tl && tr <= r) return t[node];
		int tm = (tl + tr) / 2;

		return merge (get (2 * node, tl, tm, l, r), get (2 * node + 1, tm + 1, tr, l, r));
	}
} t;

int main () {
	cin >> n >> m >> k >> d;

	t.build (n);

	for (int i = 0; i < m; i++) {
		int x, r;
		cin >> r >> x;
		t.update (r - 1, x);
		if (t.get (1, 0, t.start - 1, 0, n - 1).seg <= d * k) cout << "TAK\n";
		else cout << "NIE\n";
	}
}
