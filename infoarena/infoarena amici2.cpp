#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
//When will all vertices be connected? When two most distant ones will be. If d(a, b) is the minimal distance between a and
//b, the maximum between all d(a, b) will be called diameter of a graph. So the answer for the graph is the answer for
//its diameter. But finding diameter is O(NM). Then we can use the fact, instead X we can output X+1 and X-1. Now we should
//find some path, that is at least half of the diameter. We can choose arbitrary vertex and take the farthest node to it.
//Why? Let's say d(A, B) = diameter, Y is the farthest point to X. Y = A, B is trivial: that means X -> Y lies on diameter
//and there is a vertex T that lie in both paths, so if we go from X to T and from T to the farthest end of diameter, 
//last step will ensure us, path will be at least diameter/2. Let's say Y is not A or B. that means d(X, A) <= d(X, Y)
//and d(X, B) <= d(X, Y) -> d(X, A) + d(X, B) <= 2 * d(X, Y). Let for some minimal paths from X to A and B the last common
//vertex be T. 
//2 * d(X, T) + d(T, A) + d(T, B) <= 2 * d(X, Y)
//d(T, A) + d(T, B) <= 2 * d(X, Y) and since d(T, A) + d(T, B) <= d(A, B) (tiangle inequation works for min. distances)
//d(X, Y) >= d(A, B)/2
#include <fstream>
#include <set>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

vector <int> g[100000];

int n, m, d[100000], u[100000];

int bfs (int x) {
	queue <int> q;
	int mx = 0;
	q.push (x);
	d[x] = 0;

	while (!q.empty ()) {
		int f = q.front ();
		mx = max (mx, d[f]);

		q.pop ();

		for (int to : g[f]) {
			if (!u[to]) {
				d[to] = d[f] + 1;
				u[to] = 1;
				q.push (to);
			}
		}
	}

	return mx;
}

int main () {
	ifstream fin ("amici2.in");
	ofstream fout ("amici2.out");
	int t;

	fin >> t;

	while (t--) {
		fin >> n >> m;
		memset (u, 0, n * sizeof (int));

		for (int i = 0; i < n; i++)
			g[i].clear ();

		for (int i = 0; i < m; i++) {
			int x, y;

			fin >> x >> y;

			g[x-1].push_back (y - 1);
			g[y-1].push_back (x - 1);
		}

		int ans = bfs (0), start = 0;

		while ((1 << start) <= ans) start++;
		fout << start << '\n';
	}
}
