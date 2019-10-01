#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
//First, let's build a graph, where there is a path x -> y if player x can beat player y. Now find strongly connected
//components and conduct them into vertices to obtain DAG. Since between each pair there is either a path x -> y or y -> x,
//we have only one SCC that can't be beaten by player in other SCCs (basically, a "source" of DAG). Let's call the set of the
//players inside it "dominant set". A player can win if and only if he is in a dominant set (if he's not in dominant set, 
//he can't beat anyone from this set). Now how to quickly find the set? Let's consider M(p) - the maximal rank from all 
//courts for player p. If M(x) < M(y), x can beat y. So if we sort all players by M(p) increasing, our graph will be 
//simplified to the directed path + some back edges. Let's numerate players from now by the direct order of this path.
//The vertex 0 is in the dominant set, because we reach all other players by path edges. If y is in the dominant set,
//all 0 <= x < y are there, because there is a path 0 -> x -> y and 0 and y are in the set. So the set on this new graph
//will be the prefix of the "main" M(x) path. When can we say that the players from the prefix [0..x-1] can't be beaten
//by all other players? Prefix should contain all first x ranks from all courts, because if some rank r 1 <= r <= x for a 
//court is not there, this missing rank can be used against the player in prefix with the lowest rank on this  court. 
//So if in our prefix any player has M(k) > x, that means for some court the there is < x players with rank <= x, so some 
//high rank is missing. The set of size x is dominant if the maximal rank for each player in the set is <= x.
//But beware of sets that are obtained by merging some adjacent SCCs. They may be unbeatable, but are not dominant, so to get
//the version with one SCC we go for a minimal prefix. We can keep in t[x] = x - (the number of players with maximal rank 
// <= x) and then search a leftmost 0 with parallel binsearch in O(N + QlogN).
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int n, q, a[1000000][3], m[1000000], c[1000000];

struct SegTree {
	int t[4000000], t_add[4000000], start;

	void push (int node) {
		if (node < start) {
			t_add[2 * node] += t_add[node];
			t_add[2 * node + 1] += t_add[node];
		}
		t[node] += t_add[node];
		t_add[node] = 0;
	}

	void build (int n) {
		start = 1;
		while (start < n) start <<= 1;

		int sum = 0;

		for (int i = 0; i < n; i++) {
			sum += c[i];
			t[i + start] = i + 1 - sum;
		}

		for (int i = start - 1; i; i--)
			t[i] = min (t[2 * i], t[2 * i + 1]);
	}

	void update (int node, int tl, int tr, int l, int r, int d) {
		push (node);

		if (tr < l || r < tl) return;
		if (l <= tl && tr <= r) {
			t_add[node] += d;
			push (node);
			return;
		}

		int tm = (tl + tr) / 2;

		update (2 * node, tl, tm, l, r, d);
		update (2 * node + 1, tm + 1, tr, l, r, d);

		t[node] = min (t[2 * node], t[2 * node + 1]);
	}

	int order_stat (int node, int tl, int tr) {
		push (node);

		if (tl == tr) return tl;

		int tm = (tl + tr) / 2;

		push (2 * node);

		if (t[2 * node] == 0) return order_stat (2 * node, tl, tm);
		else return order_stat (2 * node + 1, tm + 1, tr);
	}
} t;

void update (int x) {
	t.update (1, 0, t.start - 1, m[x], n - 1, 1);
	m[x] = max (a[x][0], max (a[x][1], a[x][2]));
	t.update (1, 0, t.start - 1, m[x], n - 1, -1);
}

int main () {
	cin >> n >> q;
	for (int j = 0; j < 3; j++)
		for (int i = 0; i < n; i++) {
			int x;
			scanf ("%d", &x);
			a[x-1][j] = i;
		}

	for (int i = 0; i < n; i++) {
		m[i] = max (a[i][0], max (a[i][1], a[i][2]));
		c[m[i]]++;
	}

	t.build (n);

	for (int i = 0; i < q; i++) {
		int p, x, y, type;
		scanf ("%d", &type);

		if (type == 2) {
			scanf ("%d%d%d", &p, &x, &y);

			swap (a[x-1][p-1], a[y-1][p-1]);

			update (x - 1);
			update (y - 1);
		}
		else {
			scanf ("%d", &x);

			if (t.order_stat (1, 0, t.start - 1) >= m[x-1]) printf ("DA\n");
			else printf ("NE\n");
		}
	}
}
