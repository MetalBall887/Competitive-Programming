#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
#include <algorithm>
//try all possible final states, for each there are O(n!) possible matchings "stone -> finish point"
//the distance between a stone and a finish point is always Manhattan, because we don't care, which 
//stone will get to the point, so we can change places in 0 moves, basically swapping finishing points
//so to find a minimal matching, apply min-cost-flow.
#include <bitset>
#include <queue>
#include <math.h>
#include <stack>
#include <vector>
#include <string.h>
 
typedef long long ll;
typedef long double ld;
 
const ll MOD = 1e9 + 7, INF = 1e18 + 1;
 
using namespace std;
 
int n;

vector < pair <int, int> > a, b;

int dist (pair <int, int> x, pair <int, int> y)
{
	return abs (x.first - y.first) + abs (x.second - y.second);
}

vector <int> g[100];

int S, T, f[100][100], cost[100][100];

int find_path ()
{
	vector <int> p (T + 1, 0), d (T + 1, 1e9), inq (T + 1, 0);

	queue <int> q;

	d[S] = 0;
	inq[S] = 1;
	q.push (S);

	while (!q.empty ())
	{
		int x = q.front ();
		q.pop ();

		inq[x] = 0;

		for (int to : g[x])
			if (f[x][to] && d[to] > d[x] + cost[x][to])
			{
				d[to] = d[x] + cost[x][to];
				p[to] = x;

				if (!inq[to])
				{
					inq[to] = 1;
					q.push (to);
				}
			}
	}

	if (d[T] == 1e9) return -1e9;

	int cap = 1e9, x = T, delta = 0;

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

		delta += cost[p[x]][x] * cap;

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

int main ()
{
	int t = 0;
	while (cin >> n && n)
	{
		t++;
		for (int i = 0; i < n; i++)
			g[i].clear ();

		S = 0;
		T = 2 * n + 1;

		a.clear ();

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				g[i + 1].push_back (n + j + 1);
				g[n + j + 1].push_back (i + 1);
			}	

		for (int i = 0; i < n; i++)
		{
			g[0].push_back (i + 1);
			g[i + 1].push_back (0);
			f[0][i + 1] = 1;
			g[2 * n + 1].push_back (n + i + 1);
			g[n + i + 1].push_back (2 * n + 1);
		}

		for (int i = 0; i < n; i++)
		{
			int x, y;

			scanf ("%d%d", &x, &y);
			a.push_back ({x, y});
		}

		int mn = 1e9;

		for (int type = 0; type < 4; type++)
			for (int k = 1; k <= (type < 2 ? n : 1); k++)
			{
				b.clear ();
				memset (f, 0, sizeof (f));
				memset (cost, 0, sizeof (cost));

				for (int i = 1; i <= n; i++)
				{
					if (type == 0) b.push_back ({k, i});
					if (type == 1) b.push_back ({i, k});
					if (type == 2) b.push_back ({i, i});
					if (type == 3) b.push_back ({n - i + 1, i});
				}

				int s = 0;

				for (int i = 0; i < n; i++)
					for (int j = 0; j < n; j++)
					{
						cost[i + 1][n + j + 1] = dist (a[i], b[j]);
						cost[n + j + 1][i + 1] = -cost[i + 1][n + j + 1];
						f[i + 1][n + j + 1] = 1;

						s += dist (a[i], b[j]);
					}

				for (int i = 0; i < n; i++)
				{
					f[0][i + 1] = 1;
					f[n + i + 1][2 * n + 1] = 1;
				}

				mn = min (mn, flow ());
			}

		printf ("Board %d: %d moves required.\n\n", t, mn);
	}
}
