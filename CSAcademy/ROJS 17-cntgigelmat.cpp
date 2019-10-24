#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <set>
//Let's look at this problem diagonally. When can we say that two elements on the same diagonal? Let's for the left one
//determine the number of consequent 1's down and right and for the right one the same thing but up, left and diagonally
//up-left. The minimum of all elements of left point will be the left condition, same for the right condition. To make the pair
//minimum between those conditions should not be less than distance between points on diagonal (if we store it
//as 1D segment). We should find the number of such pairs on each diagonal. We do exactly this in functon process().
//The algorithm is a sweep line. Each turn we add 1 on element i and keep in mind that when distance from this point i to
//sweep line will be bigger than left condition of i. Each point also asks the number of points it lies inside left condition
//of. But it will pair up only with those who lie inside his right condition, so it is also a range query. That's why we need
//BIT.
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <queue>

#define N 1000000

using namespace std;

typedef long long ll;

const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

vector <int> query;
vector < pair <int, int> > reset;

struct state {
	int l, r, d, u, lu;
} d[2000][2000];

int n, m, b[2000];

char c[2000][2000];

struct BIT {
	ll t[20000];

	void update (int x, int d) {
		for (; x <= max (n, m); x = (x | (x + 1)))
			t[x] += d;
	}

	ll get (int r) {
		ll sum = 0;

		for (; r >= 0; r = (r & (r + 1)) - 1)
			sum += t[r];

		return sum;
	}

	ll get (int l, int r) {
		return get (r) - get (l - 1);
	}

	void clear () {
		memset (t, 0, sizeof (ll) * max (n, m));
	}
} t;

ll process () {
	ll n = query.size (), ans = 0, ptr = 0;
	for (int i = 0; i < query.size (); i++) {
		t.update (i, 1);
		while (ptr < reset.size () && reset[ptr].first <= i) {
			t.update (reset[ptr].second, -1);
			ptr++;
		}

		ans += t.get (i - query[i] + 1, i);
	}

	return ans;
}

int main () {
	cin >> n >> m;

	for (int i = 0; i < n; i++)
		scanf ("%s", c[i]);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			d[i][j].l = c[i][j] - '0';
			if (j && c[i][j] == '1') d[i][j].l += d[i][j-1].l;
		}

		for (int j = m - 1; j >= 0; j--) {
			d[i][j].r = c[i][j] - '0';
			if (j != m - 1 && c[i][j] == '1') d[i][j].r += d[i][j+1].r;
		}
	}

	for (int j = 0; j < m; j++) {

		for (int i = 0; i < n; i++) {
			d[i][j].u = c[i][j] - '0';
			if (i && c[i][j] == '1') d[i][j].u += d[i-1][j].u;
		}

		for (int i = n - 1; i >= 0; i--) {
			d[i][j].d = c[i][j] - '0';
			if (i != n - 1 && c[i][j] == '1') d[i][j].d += d[i+1][j].d;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			d[i][j].lu = c[i][j] - '0';
			if (i && j && c[i][j] == '1') d[i][j].lu += d[i-1][j-1].lu;
		}
	}

	ll ans = 0;

	for (int i = 0; i < n; i++) {
		reset.clear ();
		query.clear ();
		t.clear ();
		for (int j = 0; i + j < n && j < m; j++) {
			reset.emplace_back (j + min (d[i+j][j].r, d[i+j][j].d), j);
			query.push_back (min (d[i+j][j].lu, min (d[i+j][j].l, d[i+j][j].u)));
		}

		sort (reset.begin(), reset.end());

		ans += process ();
	}

	for (int j = 1; j < m; j++) {
		reset.clear ();
		query.clear ();
		t.clear ();
		for (int i = 0; i < n && i + j < m; i++) {
			reset.emplace_back (i + min (d[i][i+j].r, d[i][i+j].d), i);
			query.push_back (min (d[i][i+j].lu, min (d[i][i+j].l, d[i][i+j].u)));
		}

		sort (reset.begin(), reset.end());

		ans += process ();
	}

	cout << ans;
}
