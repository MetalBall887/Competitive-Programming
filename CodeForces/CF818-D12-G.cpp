#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
#include <algorithm>
//Slow solution using heuristics. Will try to replace it with the better one.
//The idea is, after creating a graph (i, j) -> it is possible to place a[i] and a[j] near each other in a subsequence,
//We can push exactly 4 flows with minimal overall cost to get the answer. Correct solution will use Dijkstra with potentials
//But mine uses some heuristics with SPFA, so the solution is O(n^2).
#include <bitset>
#include <queue>
#include <math.h>
#include <stack>
#include <vector>
#include <string.h>

typedef long long ll;
 
const ll MOD = 1e9 + 7, INF = 1e18 + 1;
 
using namespace std;

struct edge
{
	int u, v;
};

vector <int> g[7000];

int n, S, T, a[1000000];

short c[6010][6010], f[6010][6010];

int find_path ()
{
	vector <int> u (T + 1), p (T + 1), d (T + 1, -1e9), inq (T + 1);
	d[S] = 0;
	u[S] = 1;
	inq[S] = 1;

	queue <int> q;

	q.push (S);

	while (!q.empty ())
	{
		int x = q.front ();
		q.pop ();
		u[x] = 1;
		inq[x] = 0;

		for (int to : g[x])
		{
			if (f[x][to] && d[to] < d[x] + c[x][to])
			{
				d[to] = d[x] + c[x][to];
				p[to] = x;
				if (!inq[to])
				{
					q.push (to);
					inq[to] = 1;
				}
			}
		}
	}

	if (!u[T]) return -1e9;

	short x = T, cap = 100, delta = 0;

	while (x != S)
	{
		cap = min (cap, f[p[x]][x]);
		x = p[x];
	}
	
	x = T;

	while (x != S)
	{
		f[p[x]][x] -= cap;
		f[x][p[x]] += cap;

		delta += c[p[x]][x] * cap;

		x = p[x];
	}

	return delta;

}

int flow ()
{
	int s = 0, a;

	while ((a = find_path ()) != -1e9)
	{
		s += a;
	}

	return s;
}


void add (int u, int v, int cost)
{
	g[u].push_back (v);
	c[u][v] = cost;
	f[u][v] = 1;

	g[v].push_back (u);
	c[v][u] = -cost;
}

int main ()
{
	cin >> n;

	for (int i = 1; i <= n; i++)
		scanf ("%d", &a[i]);

	for (int i = 1; i <= n; i++)
	{
		add (2 * i - 1, 2 * i, 1);
		for (int j = i + 1; j <= min (n, i + 200); j++)
			if (abs (a[i] - a[j]) == 1 || a[i] % 7 == a[j] % 7)
				add (2 * i, 2 * j - 1, 0);
	}

	for (int i = 1; i <= n; i++)
	{
		add (2 * n + 1, 2 * i - 1, 0);
		add (2 * i, 2 * n + 2, 0);
	}

	add (0, 2 * n + 1, 0);
	f[0][2 * n + 1] = 4;

	S = 0;
	T = 2 * n + 2;

	cout << flow ();
}
