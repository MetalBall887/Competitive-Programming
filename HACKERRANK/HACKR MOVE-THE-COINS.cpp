#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
//h[i] - distance from i to root. Notice that if h[i] is odd, there should be a parent above i. That
//means, if coins go from the node with even dist, this turn can be "parried" and coins sent upwards again.
//That means, if the player with initiative wants, he can ignore all values in nodes with even height
//and if he pushes coins from the node with odd height, he doesn't expect them to return (again,
//if they return, he spends one turn to push them to parent and since he can always do it, it will always be 
//basically cancelling the last turn with his turn). Now, since they never return, we can look at this problem
//as a nim, where heaps are only in odd heighted nodes. If first player is in winning position of this nim, 
//he will do a strategy above. If he is not, every his move is adding or distracting non-zero to any heap of this nim, that 
//leads to winning position. Now how to process queries: check if it is valid by parenthesis check and
//notice that the xor of odd-height nodes will be swapped with the xor of even-height nodes if the root of subtree
//changes the parity of its height.
#include <fstream>
#include <set>
#include <cstring>
#include <assert.h>
#include <cstdlib>
#include <cmath>
#include <queue>
 
#define N 1000000
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
vector <int> g[N];

int n, x_even[N], x_odd[N], c[N], tin[N], tout[N], timer;
int h[N], q;

void dfs (int x, int p) {
	h[x] = h[p] + 1;
	tin[x] = ++timer;
	x_even[x] = c[x];

	for (int to : g[x]) 
		if (to != p) {
			dfs (to, x);
			x_even[x] ^= x_odd[to];
			x_odd[x] ^= x_even[to];
		}
	tout[x] = ++timer;
}

int main () {
	cin >> n;

	for (int i = 0; i < n; i++) {
		scanf ("%d", &c[i]);
	}
 
	for (int i = 0; i < n - 1; i++) {
		int u, v;

		scanf ("%d%d", &u, &v);

		g[u-1].push_back (v - 1);
		g[v-1].push_back (u - 1);
	}

	dfs (0, 0);

	cin >> q;

	for (int i = 0; i < q; i++) {
		int u, v;

		scanf ("%d%d", &u, &v);
		u--, v--;

		if (tin[u] < tin[v] && tout[v] < tout[u]) {
			cout << "INVALID\n";
		} else {
			if ((h[u] - h[v]) % 2 == 0) {
				int ans = x_odd[0] ^ x_even[u] ^ x_odd[u];
				if (ans) cout << "YES\n";
				else cout << "NO\n";
			}
			else {
				if (x_odd[0]) cout << "YES\n";
				else cout << "NO\n";
			}
		}
	}
}
