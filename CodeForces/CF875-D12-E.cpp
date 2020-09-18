#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>

//Let's start with a binary search by the max distance. Assume we can't have couriers being further away from each other than D meters. Let d[i] be 1 if it's 
//possible for any of them to get to the i-th point. Now let's try to make a move with the other courier. He has to greedily go to points i+1, i+2, ... until any 
//of them is too far away from the i-th one. Since we already assume they both are standing correctly, the original position of the second courier is not important
//We can find the smallest i+k such that abs(a[i], a[i+k]) > D offline with scanning line and segment tree 
//and can move the second courier up to i+k-1st point, so d[i+1], d[i+2], ... d[i+k-1] = 1. That means the set of numbers for which d[] = 1 is always a 
//prefix and we only need to keep the length for it.

//using namespace __gnu_pbds;
 
#define N 2000001
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int s[N], x[N], n, s1, s2;
 
struct SegTree {
	int t[N], start;
 
	void build (int n) {
		start = 1;
 
		while (start < n) start <<= 1;
 
		fill (t, t + 2 * start, n);
	}
 
	void update (int x, int d) {
		x += start;
		t[x] = d;
 
		x >>= 1;
 
		while (x) {
			t[x] = min (t[2 * x], t[2 * x + 1]);
			x >>= 1;
		}
	}
 
	int get (int l, int r) {
		l += start, r += start + 1;
 
		int mn = n;
 
		while (l < r) {
			if (l & 1) mn = min (mn, t[l++]);
			if (r & 1) mn = min (mn, t[--r]);
			l >>= 1, r >>= 1;
		}
 
		return mn;
	}
} t;
 
bool check (int d) {
	t.build (n);
	
	vector <int> v (n, n);
 
	for (int i = n - 1; i >= 0; i--) {
		int l = lower_bound (s, s + n, s[x[i]] - d) - s - 1;
		int r = upper_bound (s, s + n, s[x[i]] + d) - s;
		v[i] = min ((l == -1 ? n : t.get (0, l)), (r == n ? n : t.get (r, n - 1))) - 1;
		t.update (x[i], i);
	}
 
	int r = 0;
 
	for (int i = 0; i < n; i++) {
		if (i > r) return false;
		r = max (r, v[i]);
	}
 
	return true;
}
 
int main () {
	cin >> n;
	n += 2;
 
	for (int i = 0; i < n; i++) {
		cin >> x[i];
		s[i] = x[i];
	}
 
	sort (s, s + n);
 
	for (int i = 0; i < n; i++) {
		x[i] = lower_bound (s, s + n, x[i]) - s;
	}
 
	int l = 0, r = 1e9;
 
	while (l < r) {
		int d = (l + r) / 2, fst = s[x[0]];
 
		if (check (d)) r = d;
		else l = d + 1;
	}
 
	cout << l << endl;
}
