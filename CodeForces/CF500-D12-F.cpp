#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Solution that uses the fact p is fixed:
//First, notice that if all segment lengths are p, then from a time t, only items whose segments start at [t-p+1;t] intersect
//the query. Thus, we can have point items and range queries. Moreover, all ranges have a fixed size p, so if we divide
//the whole line on intervals of size p, the query range will intersect at most two of them. That means, for every interval
//we can precompute knapsack dp for every prefix and suffix of this interval in O(# of items in the interval * W) and
//for each query there will be at most one "merge" in time O(W). Thus, overall complexity will be O((n+q)W).

using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int q;
 
struct item {
	int c, h, t;
	bool operator < (const item& b) const {
		return t < b.t;
	}
} a[4000];
 
struct table {
	vector < array <int, 4001> > d;
 
	void calc (vector <item> bl) {
 
		if (!bl.size ()) return;
		d.resize (bl.size ());
 
		fill (&d[0][0], &d[0][bl[0].c - 1], 0);
 
		for (int i = bl[0].c; i <= 4000; i++) {
			d[0][i] = bl[0].h;
		}
 
		for (int i = 1; i < bl.size (); i++) {
			for (int j = 0; j <= 4000; j++) {
				d[i][j] = d[i-1][j];
				if (bl[i].c <= j) {
					d[i][j] = max (d[i][j], d[i-1][j - bl[i].c] + bl[i].h);
				}
			}
		}
	}
 
	array <int, 4001> operator[] (int x) {
		return d[x];
	} 
};
 
vector <table> dp, ds;
 
int pt[4000], s[4000], p, n;
 
 
vector <item> blocks[4000];
 
int main () {
	cin >> n >> p;
 
	for (int i = 0; i < n; i++) {
		cin >> a[i].c >> a[i].h >> a[i].t;
	}
 
	sort (a, a + n);
 
	int cur = 0;
 
	for (int i = 0; i < n; i++) {
		while ((cur + 1) * p <= a[i].t) cur++;
		blocks[cur].push_back (a[i]);
		pt[i] = blocks[cur].size () - 1;
		s[i] = cur;
	}
 
	for (int i = 0; i <= cur; i++) {
		table pref, suf;
 
		pref.calc (blocks[i]);
		reverse (blocks[i].begin(), blocks[i].end());
		suf.calc (blocks[i]);
 
		dp.push_back (pref);
		ds.push_back (suf);
	}
 
	cin >> q;
 
	for (int i = 0; i < n; i++) {
 
	}
 
	for (int i = 0; i < q; i++) {
		int t, b;
		cin >> t >> b;
 
		int l = lower_bound (a, a + n, item ({0, 0, t - p + 1})) - a;
		int r = upper_bound (a, a + n, item ({0, 0, t})) - a - 1;
		
		if (l > r) {
			cout << 0 << endl;
			continue;
		}
 
		int ans = 0;
 
		auto left = ds[s[l]][blocks[s[l]].size () - pt[l] - 1];
 
		auto right = dp[s[r]][pt[r]];
 
		if (s[l] == s[r]) {
			if (!pt[l]) ans = right[b];
			else ans = left[b];
		} else {
			for (int i = 0; i <= b; i++) {
				ans = max (ans, left[i] + right[b - i]);
			}
		}
 
		cout << ans << endl;
	}
}
