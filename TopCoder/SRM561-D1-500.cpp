#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <map>
//Since circles do not have common points, we can view inclusions in a tree structure (there is a path if one circle lies
//inside of the second one). In this tree, if we mark a circle, we mark all the circle the current one lies inside => 
//we mark all the path up to the root, dividing the tree with this to independent subtrees. We base our sprague-grundy game
//on this.
#include <map>
#include <set>
#include <cstring>
#include <assert.h>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const int INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const int N = 1e4;

struct CirclesGame {
	vector <int> g[N], mx[N];
	int d[N], u[N], p[N];

	int calc_mex (vector <int>& v) {
		sort (v.begin(), v.end());

		if (v.empty () || v[0]) return 0;

		for (int i = 1; i < v.size (); i++) {
			if (v[i-1] + 1 < v[i]) return v[i-1] + 1;
		}

		return v.back () + 1;
	}

	int count_grundy (int x, int p, int t, int acc) {
		if (x == t) {
			if (u[x]) return d[x];
			else u[x] = 1;
		}

		for (int to : g[x]) {
			if (to == p) continue;
			acc ^= count_grundy (to, x, to, 0);
		}

		mx[t].push_back (acc);

		for (int to : g[x]) {
			if (to == p) continue;
			acc ^= d[to];
			count_grundy (to, x, t, acc);
			acc ^= d[to];
		}

		if (x == t) {
			d[x] = calc_mex (mx[x]);
		}

		return d[x];
	}

	struct Circle {
		int x, y, r;
		bool operator < (const Circle& b) const {
			return r < b.r;
		}
	};

	int dist (Circle a, Circle b) {
		Circle d = {a.x - b.x, a.y - b.y, a.r};
		return d.x * d.x + d.y * d.y;
	}

	string whoCanWin (vector <int> x, vector <int> y, vector <int> r) {
		int n = x.size ();

		vector<Circle> v (n);

		for (int i = 0; i < n; i++) {
			v[i] = {x[i], y[i], r[i]};
		}

		sort (v.begin(), v.end());
		memset (p, -1, sizeof (p));

		for (int i = 0; i < n; i++)
			for (int j = 0; j < i; j++) {
				if (dist (v[i], v[j]) <= v[i].r * v[i].r && p[j] == -1) {
					g[i].push_back (j);
					p[j] = i;
				}
			}

		int ans = 0;

		for (int i = 0; i < n; i++) {
			if (p[i] == -1) ans ^= count_grundy (i, -1, i, 0);
		}

		if (ans) return "Alice";
		else return "Bob";
	}
};
