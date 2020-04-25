#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Let's assume some part of our field is already ploughed. Notice that there can't be vertical stripes above the unploughed
//rectangle and the same holds for each direction. That particularly means that for the last stripe there will be only stripes
//of the same orientation from both sides -> after ploughing there will be either m vertical stripes or n horizontal stripes.
//Now assume we have m vertical stripes. Let's try to plough the field. We know that there will be vertical stripes on each
//column, so if we can plough vertically, we do it. If we can't, we have to decide either we plough the top or the bottom.
//It's actually a hard choice that will lead us to slow solutions, so instead we will limit the number of ploughs above and
//below, so let check(lo, hi) be True iff it's possible to plough the field with using at most lo lower ploughs and at most
//hi higher ploughs. Now, since we can't really "skip" rows (if we take hi higher stripes, we will take them from rows [1;hi]), 
//if it's not possible to add vertical stripes, we can add horizontal stripes greedily. If f(x) is the smallest number such 
//that check (x, f(x)) is true, the minimum will be m + x + f(x) for some x. To calculate f(x) for each x, note that 
//f(x+1)<=f(x), so we can use two pointers method.

using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int p[2000][2000], a[2000][2000], d[2000][2000], n, m;
int k, ans = N;

int sum (int l1, int r1, int l2, int r2) {
	int s = p[l2][r2];
	if (l1) s -= p[l1-1][r2];
	if (r1) s -= p[l2][r1-1];
	if (l1 && r1) s += p[l1-1][r1-1];
	return s;
}

bool check (int a, int b) {
	int l = 0, r = m - 1, lo = 0, hi = n - 1;

	while (l <= r && lo <= hi) {
		if (sum (lo, l, hi, l) <= k) l++;
		else if (sum (lo, r, hi, r) <= k) r--;
		else if (sum (lo, l, lo, r) <= k && a) { a--, lo++; }
		else if (sum (hi, l, hi, r) <= k && b) { b--, hi--; } 
		else return false;
	}
	return true;
}

int main () {
	ios::sync_with_stdio (0);
	cin.tie (NULL);
	cin >> k >> m >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
			p[i][j] = a[i][j];
			if (i) p[i][j] += p[i-1][j];
			if (j) p[i][j] += p[i][j-1];
			if (i && j) p[i][j] -= p[i-1][j-1];
		}
	}

	int j = n;

	for (int i = 0; i < n; i++) {
		while (j > 0 && check (i, j - 1)) j--;
		if (check (i, j)) ans = min (ans, m + i + j);
	}


	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			d[j][i] = a[i][j];
		}
	}

	swap (n, m);


	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			p[i][j] = d[i][j];
			if (i) p[i][j] += p[i-1][j];
			if (j) p[i][j] += p[i][j-1];
			if (i && j) p[i][j] -= p[i-1][j-1];
		}
	}

	j = n;

	for (int i = 0; i < n; i++) {
		while (j > 0 && check (i, j - 1)) j--;
		ans = min (ans, m + i + j);
	}

	cout << ans;
}
