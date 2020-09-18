#include <bits/stdc++.h>
#define int ll
//#include <ext/pb_ds/assoc_container.hpp>
//Note that whenever we take take the modulo, it's either the same number or at least twice smaller than the original one. That means, if you take the modulo
//only when it changes, there will be at most nlogA modulo operations. For taking modulo x on a range we can always take a modulo of a maximal number while it's
//>= x.
 
//using namespace __gnu_pbds;
 
#define N 2000001
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int a[N], n, m;
 
struct SegTree {
	int t_sum[N], t_max[N], start;
 
	int merge_ind (int l, int r) {
		return a[l] > a[r] ? l : r;
	}
 
	int merge (int l, int r) {
		return merge_ind (t_max[l], t_max[r]);
	}
 
	void build (int n) {
		start = 1;
 
		while (start < n) start <<= 1;
 
		for (int i = 0; i < n; i++) {
			t_sum[i + start] = a[i];
			t_max[i + start] = i;
		}
 
		for (int i = start - 1; i; i--) {
			t_sum[i] = t_sum[2 * i] + t_sum[2 * i + 1];
			t_max[i] = merge (2 * i, 2 * i + 1);
		}
	}
 
	void update (int x, int d) {
		x += start;
 
		t_sum[x] = d;
		a[x - start] = d;
		x >>= 1;
 
		while (x) {
			t_sum[x] = t_sum[2 * x] + t_sum[2 * x + 1];
			t_max[x] = merge (2 * x, 2 * x + 1);
			x >>= 1;
		}
	}
 
	int get_max (int l, int r) {
		l += start, r += start + 1;
		int mx = l - start;
 
		while (l < r) {
			if (l & 1) mx = merge_ind (t_max[l++], mx);
			if (r & 1) mx = merge_ind (t_max[--r], mx);
			l >>= 1, r >>= 1;
		}
 
		return mx;
	}
 
	int get_sum (int l, int r) {
		l += start, r += start + 1;
		int sum = 0;
 
		while (l < r) {
			if (l & 1) sum += t_sum[l++];
			if (r & 1) sum += t_sum[--r];
			l >>= 1, r >>= 1;
		}
 
		return sum;
	}
} t;
 
signed main () {
	cin >> n >> m;
 
	for (int i = 0; i < n; i++)
		cin >> a[i];
 
	t.build (n);
 
	for (int i = 0; i < m; i++) {
		int c, l, r, x, d;
		cin >> c;
 
		if (c == 1) {
			cin >> l >> r;
			l--, r--;
 
			cout << t.get_sum (l, r) << '\n';
		}
 
		if (c == 2) {
			cin >> l >> r >> x;
			l--, r--;
			
			while (a[t.get_max(l, r)] >= x) {
				int v = t.get_max(l, r);
				t.update (v, a[v] % x);
			}
		}
 
		if (c == 3) {
			cin >> x >> d;
			x--;
			t.update (x, d);
		}
	}
}
