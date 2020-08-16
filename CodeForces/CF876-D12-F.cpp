#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
 
//using namespace __gnu_pbds;
//For each mountain find the largest range on which it will be the highest. Now let's compute the same number but with a fixed maximum. All ranges will contain this
//maximum, find the closest number from the left and from the right (inside the range) that contains the bit our maximum doesn't contain. If any range will contain
//one of these mountains with the current maximum (being the maximum on this range), it will satisfy the rule. Now it's easier to count the number of ranges that
//don't satisfy the rule and have the fixed mountain as (rightmost in case of tie) maximum.
 
#define N 1000000
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const int M = 1e6;
 
ll n, a[N], ans;
 
struct SegTree {
	int t[N], start;
 
	int merge (int i, int j) {
		if (i > j) swap (i, j);
		if (a[i] > a[j]) return i;
		return j;
	}
 
	void build (int n) {
		start = 1;
 
		while (start < n) start <<= 1;
 
		for (int i = 0; i < start; i++) {
			t[i + start] = i;
		}
 
		for (int i = start - 1; i; i--) {
			t[i] = merge (t[2 * i], t[2 * i + 1]);
		}
	}
 
	int get (int l, int r) {
		int c = l;
		l += start, r += start + 1;
 
		while (l < r) {
			if (l & 1) c = merge (c, t[l++]);
			if (r & 1) c = merge (c, t[--r]);
 
			l >>= 1, r >>= 1;
		}
 
		return c;
	}
} t;
 
int bl[200000][30], br[200000][30];
 
void Rec (int l, int r) {
	if (l > r) return;
	int x = t.get (l, r), tl = l - 1, tr = r + 1;
 
	for (int i = 0; i < 30; i++)
		if ((a[x] >> i) % 2 == 0) {
			tl = max (tl, bl[x][i]);
			tr = min (tr, br[x][i]);
		}
 
	ans += (ll) (x - tl) * (tr - x);
 
	Rec (l, x - 1);
	Rec (x + 1, r);
}
 
int main () {
	cin >> n;
 
	fill (a, a + 2 * n, (int) -1e9);
 
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
 
	t.build (n);
 
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 30; j++) {
			bl[i][j] = (i ? bl[i-1][j] : -1);
 
			if ((a[i] >> j) & 1) bl[i][j] = i;
		}
	}
 
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < 30; j++) {
			br[i][j] = (i != n - 1 ? br[i+1][j] : n);
			if ((a[i] >> j) & 1) br[i][j] = i;
		}
	}
 
	Rec (0, n - 1);
 
	ans = n * (n + 1) / 2 - ans;
 
	cout << ans;
}
