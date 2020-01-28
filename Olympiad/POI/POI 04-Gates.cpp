#include <bits/stdc++.h>
//Let's first solve the problem for acyclic graphs. We can sort them topologically and start from the sources. Let's suppose
//all vertices we've already processed are valid and output states are minimized (minimum exists because changing the output
//states to 0, if possible, can't increase the state of other outputs in any way, so it's always optimal to do so). That means,
//if some of the output states there are not 0, there is no possible arrangement for them to be 0 and if some are 1, they will 
//always be 1. That is the key observation for this problem. Also that means, for the current vertex, the output state 
//calculated from his inputs will also be minimized. For cyclic graphs, we can decompose them to SCCs, contract the graph
//SCC -> vertex and we will obtain an acyclic graph. How to deal with an SCC? Let's try to bound output states from the bottom
//Output states, that enter the SCC from its predecessors have their lower bounds equal to their actual values due to 
//minimality as explained above. At the start, all in-SCC lower bounds (lb's) are 0. If for some vertex from the sum of lb's 
//of input states you can get the lb for the output state that is better than the current one, improve it and since output
//state has changed, some of the input states have changed for some vertices as well, so we should try to improve the lb in 
//those vertices too. Keep improving the lower bounds until you get a valid SCC, which will mean all lower bounds are also
//valid output states -> those states are minimal. If we use dfs for propagating changes to children, each node will be
//visited if one of his parents will increase his lb. Each node can increase lb only twice, which will lead us to O(m)
//complexity for an SCC. For a graph this will be O(n + m).
 
#define N 1000001
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int n, m, u[10000], st[10000][2], color, col[10000];
vector <int> in[10000], out[10000], v, d[10000];
int sm[10000];
void topsort (int x) {
	u[x] = 1;
	for (int to : out[x])
		if (!u[to]) topsort (to);
	v.push_back (x);
}

void dfs (int x) {
	u[x] = 1;
	for (int to : in[x])
		if (!u[to]) dfs (to);
	d[color].push_back (x);
	col[x] = color;
}

int upd (int x) {
	return (x < 2 ? (x << 1) : ((sm[x] >= 0) + (sm[x] > 0)));
}

void propagate (int x, int c, int j) {
	int p = st[x][j];
	st[x][j] = upd (x);
	for (int to : out[x]) {
		if (col[to] != c) continue;
		if (p == 2) sm[to]--;
		if (p == 0) sm[to]++;
		if (st[x][j] == 2) sm[to]++;
		if (st[x][j] == 0) sm[to]--;
		if (upd (to) != st[to][j]) propagate (to, c, j);
	}
}

void check (int c) {
	for (int j = 0; j < 2; j++) {
		for (int x : d[c]) sm[x] = 0;
		for (int x : d[c]) {
			for (int to : in[x]) {
				if (st[to][j] == 0) sm[x]--;
				if (st[to][j] == 2) sm[x]++;
			}
		}

		for (int x : d[c]) {
			if (st[x][j] != upd (x))
				propagate (x, c, j);
		}
	}
}

int main () {
	ios::sync_with_stdio (0);
	cin.tie (NULL);
	cin >> n;

	for (int i = 2; i < n; i++) {
		int k;
		cin >> k;

		for (int j = 0; j < k; j++) {
			int x;
			cin >> x;
			in[i].push_back (x);
			out[x].push_back (i);
		}
	}

	for (int i = 0; i < n; i++)
		if (!u[i]) topsort (i);

	memset (u, 0, sizeof (u));
	for (int i = 0; i < n; i++)
		st[i][1] = 2;

	for (int i = n - 1; i >= 0; i--) {
		if (!u[v[i]]) {
			dfs (v[i]);
			color++;
		}
	}

	for (int i = 0; i < color; i++) {
		check (i);
	}

	for (int i = 0; i < n; i++) {
		if (st[i][0] != st[i][1]) cout << "?\n";
		else {
			if (st[i][0] == 0) cout << "0\n";
			if (st[i][0] == 1) cout << "1/2\n";
			if (st[i][0] == 2) cout << "1\n";
		}
	}
}
