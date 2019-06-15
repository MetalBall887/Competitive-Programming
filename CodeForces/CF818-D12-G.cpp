#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
#include <algorithm>
//The idea is, after creating a graph where (i, j) edge exists when a[i] and a[j] can be near each other in a subsequence
//We have to find four vertex-disjoint paths with maximal overall sum. This is min-cost-max-flow problem. But the 
//thing is, usual MCMF with Bellman-Ford works in O(N^3), which is TLE so we have to use a trick called Dijkstra with
//potentials, which will reduce the complexity to O(Mlogn), O(N^2logn) in the worst case.
#include <bitset>
#include <queue>
#include <math.h>
#include <stack>
#include <vector>
#include <string.h>

typedef long long ll;
 
const ll MOD = 1e9 + 7, INF = 1e18 + 1;
 
using namespace std;

vector <int> g[7000];

int n, S, T, a[1000000], dp[6000], last_m[7], last[100001];

int c[6010][6010], f[6010][6010];

int c_p (int u, int v)
{
	return c[u][v] - dp[v] + dp[u];
}

int find_path ()
{
	vector <int> u (T + 1), p (T + 1), d (T + 1, 1e9);
	d[S] = 0;
	u[S] = 1;

	priority_queue < pair <int, int> > q;

	q.push ({0, S});

	while (!q.empty ())
	{
		auto fr = q.top ();
		q.pop ();
		if (fr.first != -d[fr.second]) continue;

		int x = fr.second;

		u[x] = 1;

		for (int to : g[x])
		{
			if (f[x][to] && d[to] > d[x] + c_p (x, to))
			{
				d[to] = d[x] + c_p (x, to);
				p[to] = x;
				q.push (make_pair (-d[to], to));
			}
		}
	}

	for (int i = 0; i <= T; i++)
		dp[i] += d[i];

	if (!u[T]) return -1e9;

	int x = T, cap = 100, delta = 0;

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
		s -= a;

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

	vector <int> d (n + 1);

	int mn = 1e9;

	for (int i = 1; i <= n; i++)
		scanf ("%d", &a[i]);

	for (int i = 1; i <= n; i++)
	{
		add (2 * i - 1, 2 * i, -1);
		for (int j = i + 1; j <= n; j++)
			if (abs (a[i] - a[j]) == 1 || a[i] % 7 == a[j] % 7)
				add (2 * i, 2 * j - 1, 0);
	}

	for (int i = 1; i <= n; i++)
	{
		add (0, 2 * i - 1, 0);
		add (2 * i, 2 * n + 1, 0);
	}

	add (2 * n + 1, 2 * n + 2, 0);
	f[2 * n + 1][2 * n + 2] = 4;

	S = 0;
	T = 2 * n + 2;

	for (int i = 0; i <= T; i++)
		for (int j = 0; j < i; j++)
			if (f[j][i] && dp[j] + c[j][i] < dp[i])
				dp[i] = dp[j] + c[j][i];

	cout << flow ();
}
