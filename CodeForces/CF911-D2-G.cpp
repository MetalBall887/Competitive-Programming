#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

//Let's run a scanning line on elements and for each element remember all changes applied and their order. For the current element we want to quickly find the
//composition of all these changes and quickly add or delete a new one. It can be done with a segment tree, where for a corresponding node in [l;r] there is 
//a map - composition of changes from l to r in the order of input. If the scanning line is not in the range of i-th query, there is an identical map instead.
//map in [l;r] (h) is a composition of maps from [l;m] (f) and [m+1;r] (g), so h(x) = g(f(x)), since g is on the right and is applied later. In root there will
//be a composition of all changes in the scope of current scanning line. If we enter a range of i-th query, change [i;i] map to this one change, when leaving
//make map identical again.

using namespace __gnu_pbds;
 
#define N 800003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
typedef array <short, 101> per; 
 
per v_id;
 
int a[N], n, a_max, q;
 
struct SegTree {
	per t[N];
	int start;
 
	void build (int n) {
		start = 1;
		while (start < n) start <<= 1;
 
		for (int i = 0; i < 2 * start; i++)
			t[i] = v_id;
	}
 
	per merge (const per& a, const per& b) {
		per v;
 
		for (int i = 0; i <= 100; i++) {
			v[i] = b[a[i]];
		}
 
		return v;
	}
 
	void update (int x, int a, int b) {
		x += start;
		t[x][a] = b;
		x >>= 1;
 
		while (x) {
			t[x] = merge (t[2 * x], t[2 * x + 1]);
			x >>= 1;
		}
	}
} t;
 
struct query {
	int x, a, b, id;
};
 
vector <query> qu;
 
int main () {
	cin >> n;
 
	for (int i = 0; i < n; i++)
		cin >> a[i];
 
	for (int i = 0; i <= 100; i++)
		v_id[i] = i;
 
	cin >> q;
	t.build (q);
 
	for (int i = 0; i < q; i++) {
		int l, r, a, b;
		cin >> l >> r >> a >> b;
		l--, r--;
		qu.push_back ({l, a, b, i});
		qu.push_back ({r + 1, a, a, i});
	}
 
	sort (qu.begin(), qu.end(), [&] (query a, query b) {
		return a.x < b.x;
	});
 
	int r = 0;
 
	for (int i = 0; i < n; i++) {
		while (r < qu.size () && i == qu[r].x) {
			t.update (qu[r].id, qu[r].a, qu[r].b);
			r++;
		}
 
		cout << t.t[1][a[i]] << ' ';
	}
}
