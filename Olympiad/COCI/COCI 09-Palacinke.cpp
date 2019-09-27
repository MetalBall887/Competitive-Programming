#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
//First, consider a typical problem of finding the number of ways of length k from node i to node j. Let's do a
//d_k[i][j]. Then, if there is an edge (s, j), for all d_k+1[i][j] = sum of all d_k[i][s]. Or, 
//d_k+1[i][j] = sum for s (d_k[i][s] * g[s][j]). It's multiplicating initial matrix d on g k times, so we first
//raise g into power k first in O(n^3logk). Let's apply it on this problem. d_k[i] - the number of ways from 1 to i
//in k steps. First of all, our path might stop
//at shops. that means, we propagate the value of d_k to both d_k+1 and d_k+2. So we need to store edges from
//both d_k-2 and d_k-1 to d_k in our exponentiated matrix (d_k[j] = d_k-2[j] + d_k-1[j] + ...).
//Also we have to modify our matrix with cumulative value (sum_k = sum_k-1 + d_k-1[1]) that will show you the 
//numbrt of ways from 1 to 1 in <= k steps. Last but not least, excluding some paths. We know that we should exclude
//all paths that don't contain at least one of the ingredients. We can do it through inclusion-exclusion by counting the number
//of ways without going to shops that contain some special ingredient(s) by simply removing some of the shop-edges.
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 5557, MOD2 = 1e6 + 3;

int n, sz, m, ans, T;

int g[100][100], sub[100][100];

struct Matrix {
	int a[100][100];

	Matrix (int k) {
		memset (a, 0, sizeof (a));

		for (int i = 0; i < sz; i++)
			a[i][i] = k;
	}

	int* operator[] (const int& x) {
		return a[x];
	}
};

Matrix mult (Matrix a, Matrix b) {
	Matrix c (0);

	for (int i = 0; i < sz; i++)
		for (int j = 0; j < sz; j++)
			for (int k = 0; k < sz; k++)
				c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;

	return c;
}

Matrix qpow (Matrix a, int b) {
	Matrix s (1);

	while (b) {
		if (b & 1) s = mult (s, a);
		b >>= 1;
		a = mult (a, a);
	}

	return s;
}

int process_mask (int mask) {
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (g[i][j] && (mask & g[i][j]) == 0) sub[i][j] = 1;
			else sub[i][j] = 0;
		}

	sz = 2 * n + 1;

	Matrix a (0), b (0);

	for (int j = 0; j < n; j++) {
		b[2 * j][2 * j + 1] = 1;

		for (int i = 0; i < n; i++)
			if (g[i][j]) {
				b[2 * i][2 * j] = 1;
				if (sub[i][j]) b[2 * i + 1][2 * j] = 1;
			}
	}

	b[0][2 * n] = 1;
	b[2 * n][2 * n] = 1;

	a[0][0] = 1;

	a = mult (a, qpow (b, T));

	return (a[0][2 * n] + a[0][0]) % MOD;
}

int main () {
	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int a, b;
		string s;
		cin >> a >> b >> s;

		for (char c : s) {
			if (c == 'B') g[a-1][b-1] |= 1;
			if (c == 'M') g[a-1][b-1] |= 2;
			if (c == 'J') g[a-1][b-1] |= 4;
			if (c == 'P') g[a-1][b-1] |= 8;
		}
	}

	cin >> T;

	for (int i = 0; i < 16; i++) {
		int cnt = 0;
		for (int j = 0; j < 4; j++)
			if (i & (1 << j)) cnt++;

		if (cnt & 1) ans -= process_mask (i);
		else ans += process_mask (i);
		if (ans < 0) ans += MOD;
		if (ans >= MOD) ans -= MOD;

	}

	cout << ans;
}
