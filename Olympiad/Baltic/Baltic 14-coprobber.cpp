#include "coprobber.h"
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Let node (i, j, t) be the state, where the cop is at node i, the robber is at node j and when t is 1, it's robber's turn.
//(i, i, t) are losing nodes, so we can start the game analysis from them. d[node] is 1 if current player wins, 0 if loses and
//2 if undefined. Start a bfs from all (i, i, t), for each nodes if all nodes, connected with this one are winning, the actual
//node is losing, if there is a losing position accessible, this one is winning. Instead, we do bfs only on nodes we know the
//state of, so if it's losing make all nodes from which this one is accessible winning, instead delete it and make new leaves
//losing. After this there might be positions that remained undefined. That means, they have no losing nodes accessible, so
//some of accessible nodes are winning, some are undefined as well. That also means, there is a way for a robber to continue
//the pursiut for an undefinite time, so the robber wins.
 
using namespace __gnu_pbds;
 
#define N 1000003
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int d[500][500][2], dg[500][500][2], m, n;
int mv[500][500][2], gl, sm[500];
bool a[500][500];
 
bool is_n (int x, int y, int t, int i) {
	if (t) return a[x][i] || (x == i);
	return a[y][i];
}
 
int start (int v, bool A[][500]) {
	n = v;
	m = 2 * n * n;
 
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			sm[i] += (int) A[i][j];
	memcpy (a, A, sizeof (a));
 
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			dg[i][j][0] = sm[i] + 1;
			dg[i][j][1] = sm[j];
			d[i][j][0] = d[i][j][1] = 2;
		}
 
	queue <tuple <int, int, int>> q;
 
 
	for (int i = 0; i < n; i++) {
		d[i][i][0] = 1, d[i][i][1] = 0;
		q.push ({i, i, 0}), q.push ({i, i, 1});
	}
 
	while (!q.empty ()) {
		auto s = q.front ();
		int x, y, t;
		tie (x, y, t) = s;
		q.pop ();
		for (int i = 0; i < n; i++) {
			if (is_n (x, y, t, i)) {
				int a = x, b = y, c = !t;
				if (t) a = i; else b = i;
				if (d[a][b][c] != 2) continue;
				if (!d[x][y][t]) {
					d[a][b][c] = 1, mv[a][b][c] = x;
					q.push ({a, b, c});
				} else {
					if (--dg[a][b][c] < 1) {
						d[a][b][c] = 0;
						q.push ({a, b, c});
					}
				}
			}
		}
	}
 
	for (int i = 0; i < n; i++) {
		int ok = 1;
		for (int j = 0; j < n; j++) {
			if (d[i][j][0] != 1) {
				ok = 0; break;
			}
		}
		if (ok) return gl = i;
	}
	return -1;
}
 
int nextMove (int x) {
	return gl = mv[gl][x][0];
}
