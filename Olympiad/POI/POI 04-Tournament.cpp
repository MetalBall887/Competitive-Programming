#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
//So how can we represent a tournament on graph? Let's call a graph where there is an edge (a, b) if a directly
//beat b in tournament a tournament tree. It can be used as a possible scenario of tournament. 
//So if we can build a tournament tree with root x as a subgraph of graph G, where (a, b)
//means a has chances against b, x has chances of winning the ournament. That means, it is possible that tournament table
//will turn out like in that tree. In a graph given us if there is no edge between a and b, there are actually both possibilities,
//so in G there will be both (a, b) and (b, a). Since between each pair of nodes there is at least one node, in
//G there will be only one source SCC (one to which no other SCCs have in-edge). All nodes from that source SCC are root
//of some tournament trees, same logic, no trees rooted not in those nodes can't contain nodes from source SCC. So we should
//find SCCs of graph G' = G + (complimentary to unordered version of G) and find the source SCC. But there will be up to N^2 nodes in
//such graph. But notice an interesting thing. For each vertex, degree in G means the number of nodes with dist > 1, so
//it is also the upper bound for number of vertices, not strongly connected with this vertex in G'. If we pick a vertex with
//minimal degree (v) in G, degree will be min (n, 2m/n) => O(sqrtm). So if we condensate all vertices directly strongly
//connected with v in G' (primary condesation), there will be only O(sqrtm) vertices left and we can use any quadratic 
//algorithm.
#include <bitset>
#include <algorithm>
#include <vector>
#include <math.h>
#include <set>
 
using namespace std;
 
typedef long long ll;
 
vector <int> g[100000];

int g_c[1500][1500];
 
int tin[100000], fup[100000], cnt[100000], color, dominant, passed;
int d[100000], c_prim[100000], inv_p[100000], cnt_prim;
int inv_prim[100000], c[100000], n, m, timer, ptr;
bitset <100000> st, in_prim, out_prim, primary;
 
vector <int> s;
 
void SCC (int x) {
	tin[x] = ++timer;
	fup[x] = tin[x];
	s.push_back (x);
	st[x] = 1;
	passed++;

	for (int i = 0; i <= ptr; i++) {
		if (!g_c[x][i]) continue;
		int to = i;
		if (!tin[to]) {
			SCC (to);
			fup[x] = min (fup[x], fup[to]);
		}
		else if (st[to]) {
			fup[x] = min (fup[x], tin[to]);
		}
	}

	if (tin[x] == fup[x]) {
		int cur;
		++color;
		do {
			cur = s.back ();
			s.pop_back ();
			st[cur] = 0;
			c[cur] = color;
		}
		while (cur != x);
	}
}
 
int main () {
	cin >> n;
 
	for (int i = 0; i < n; i++) {
		int k;
		scanf ("%d", &k);
		for (int j = 0; j < k; j++) {
			int x;
			scanf ("%d", &x);
			g[i].push_back (x - 1);
			d[i]++;
			d[x-1]++;
		}
	}
 
	//primary condensation
	int mn = 0;
	for (int i = 0; i < n; i++) {
		if (d[i] < d[mn]) mn = i;
	}
	primary.set ();
 
	for (int to : g[mn])
		primary[to] = 0;
 
	for (int i = 0; i < n; i++)
		for (int to : g[i]) {
			if (to == mn) primary[i] = 0;
		}
 
	for (int i = 0; i < n; i++) {
			if (primary[i]) {
				cnt_prim++;
				for (int to : g[i]) {
					out_prim[to] = 1;
					cnt[to]++;
				}
			}
			else {
				for (int to : g[i])
					if (primary[to]) {
						in_prim[i] = 1;
						cnt[i]++;
					}
			}
	}
 
	for (int i = 0; i < n; i++) {
		if (!primary[i]) {
			c_prim[++ptr] = i;
			inv_prim[i] = ptr;
			if (cnt[i] != cnt_prim || in_prim[i]) g_c[ptr][0] = 1;
			if (cnt[i] != cnt_prim || out_prim[i]) g_c[0][ptr] = 1;
		}
	}
 
	for (int i = 1; i <= ptr; i++) {
		for (int to : g[c_prim[i]])
			if (!primary[to]) {
				g_c[i][inv_prim[to]] = 1;
			}
	}

	for (int i = 0; i <= ptr; i++) {
		for (int j = 0; j <= ptr; j++) {
			if (i != j && !g_c[i][j] && !g_c[j][i])
				g_c[i][j] = g_c[j][i] = 1;
		}
	}
 
	//secondary condensation
 
 	for (int i = 0; i <= ptr; i++)
		if (!tin[i]) {
			SCC (i);
			if (passed == ptr + 1) {
				dominant = color;
			}
		}

	vector <int> ans;

	for (int i = 0; i < n; i++) {
		if (c[inv_prim[i]] == dominant) ans.push_back (i + 1);
	}

	cout << ans.size () << ' ';

	for (int a : ans)
		printf ("%d ", a);

}
