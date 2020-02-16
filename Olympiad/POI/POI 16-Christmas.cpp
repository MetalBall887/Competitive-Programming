#include <bits/stdc++.h>
//We will fix the length of blocks in powers of two. In this way, we can represent one block in O(logn) binary blocks, also
//there are only O(logn) different sizes of blocks overall. For each different size construct their own graph. How to merge
//those graphs in a graph of block size 1? We know that if there is an edge between [a, a + l) and [b, b + l), there will
//be edges between pairs [a, a + l/2), [b, b + l/2) and [a + l/2, a + l), [b + l/2, b + l) in graphs with lower block size.
//Since there are O(logn) such layers and on any layer the number of edges doubles, we could've ended up with O(n^2) edges
//but if we keep information about connected components in layers in DSU, we can be sure the number of edges on any layer
//will not exceed n, because DSU is a forest.
 
using namespace std;
 
typedef long long ll;

const int N = 1e6 + 1, inf = 1e9;
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int p[N][20], n, m;

int find (int x, int l) {
	if (p[x][l] == x) return x;
	return p[x][l] = find (p[x][l], l);
}

void unite (int a, int b, int l) {
	a = find (a, l), b = find (b, l);
	if (a != b) p[b][l] = a;
}

int main () {
	cin >> n >> m;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < 20; j++)
			p[i][j] = i;

	for (int i = 0; i < m; i++) {
		int a, b, l;
		cin >> a >> b >> l;
		a--, b--;
		for (int j = 0; j < 20; j++) {
			if (l & (1 << j)) {
				unite (a, b, j);
				a += (1 << j), b += (1 << j);
			}
		}
	}

	for (int j = 19; j > 0; j--) {
		for (int i = 0; i < n; i++) {
			if (p[i][j] != i) {
				int b = (1 << (j - 1));
				unite (i, p[i][j], j - 1);
				unite (i + b, p[i][j] + b, j - 1);
			}
		}
	}

	int ans = 0;
	for (int i = 0; i < n; i++) {
		if (p[i][0] == i) ans++;
	}

	cout << ans;
}
