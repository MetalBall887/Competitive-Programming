#include <bits/stdc++.h>
//The straightforward solution is to do a complete recursive search with using bit operations which would have the O(2^n) complexity. Unfortunately, this does not
//pass the time constraint but simply limiting the search where it does will not get an equal partition (when we know that for a smaller part if we
//put all "unseen" vertices in this part it still will not have n/2 vertices) we don't have to continue. It seems like a simple heuristic but let's look at the
//complete search tree. In each stat it will have two possibilities: current vertex will be in the left or in the right part. Once one of the parts is of size
//n, all states from that moment will have only one possibility: to go to the other part. If not this, all non-leafs would have degree 2 and the number of vertices
//will be almost twice the number of leafs, so the solution will be O(#of partitions). But because of branch cutting we have some vertices of degree 1. If the
//last k vertices in a partition went to the same part, k last ancestors of the corresponding leaf will have degree 1. The overall number of vertices is
//C[2n][n] + sum_over_k((k+1)C[2n-k][n]), which is O(C[2n][n]) = O(#of partitions).

using namespace std;

typedef long long ll;
typedef long double ld;

const int N = 2000000;
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int n, m, ans = 1e9, sum, g[30], min_bm;

void Rec (int st, int bm, int left) {
	int right = st - left;
	
	if ((n / 2 - right) > (n - st)) return; 
	if ((n / 2 - left) > (n - st)) return;

	if (st == n) {

		if (sum < ans) {
			sum = ans;
			min_bm = bm;
		}
		return;
	}

	int cut_left = __builtin_popcount(g[st] & (~bm & ((1 << st) - 1)));
	int cut_right = __builtin_popcount(g[st] & (bm & ((1 << st) - 1)));

	sum += cut_left;

	Rec (st + 1, bm | (1 << st), left);

	sum += cut_right - cut_left;

	Rec (st + 1, bm, left + 1);
	sum -= cut_right;
}

int main () {
	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		if (u > v) swap (u, v);
		g[u] |= (1 << v);
		g[v] |= (1 << u);
	}

	Rec (0, 0, 0);

	for (int i = 0; i < n; i++) {
		if (min_bm & (1 << i)) cout << i + 1 << ' ';
	}
	cout << endl;
}
