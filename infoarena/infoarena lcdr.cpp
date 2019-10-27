#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <set>
//d[i][j] - the maximal width of a rectangle with upper side on i and lower side on j. We can fill it by doing an 1D longest
//subsequence on each pair of rows, which is O(n^3). Then rearrange these cells in t[k][i] - max. width for upper point in i
//and length k. Implement it as an array of segment trees.
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int n, m, d[500][501], p[500][500], q;

string s[500];

struct SegTree {
	int t[2000], start;

	void build (int n) {
		start = 1;
		while (start < n) start <<= 1;
	}

	void update (int x, int d) {
		x += start;
		t[x] = d;
		x >>= 1;

		while (x) {
			t[x] = max (t[2 * x], t[2 * x + 1]);
			x >>= 1;
		}
	}

	int get (int l, int r) {
		l += start;
		r += start + 1;

		int mx = 0;

		while (l < r) {
			if (l & 1) mx = max (mx, t[l++]);
			if (r & 1) mx = max (mx, t[--r]);
			l >>= 1;
			r >>= 1;
		}

		return mx;
	}
} t[501];

int main () {
	ifstream fin ("lcdr.in");
	ofstream fout ("lcdr.out");

	fin >> n >> m >> q;

	for (int i = 0; i < n; i++) {
		fin >> s[i];
		t[i].build (n);

		for (int j = 0; j < m; j++) {
			p[i][j] = (s[i][j] - '0') + (i ? p[i-1][j] : 0);
		}
	}

	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++) {
			int cur = 0;

			for (int k = 0; k < m; k++) {
				if (p[j][k] - (i ? p[i-1][k] : 0) < j - i + 1) cur = 0;
				else cur++;
				d[i][j] = max (d[i][j], cur);
			}

			t[j-i+1].update (i, d[i][j]);
		}

	for (int i = 0; i < q; i++) {
		int l, c, l1, l2;
		fin >> l >> c >> l1 >> l2;

		fout << (l2 - l1 + 1 >= l && c <= t[l].get (l1 - 1, l2 - l)) << '\n';
	}
}
