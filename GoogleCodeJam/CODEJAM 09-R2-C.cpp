#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <vector>
//key idea: if chart B is under chart A and chart C is under chart B, chart C is under chart A. That means, each overlaid chart can be
//decomposed into a sequence of charts one lying under another. If we create a graph where there is an edge (u, v) if the u-th chart is
//above v-th, then each overlaid chart is a path in this graph. We have to decompose this DAG into paths that way each vertex is in exactly
//one path. We can do it with bipartite matching, finding minimal path cover of DAG is a classic problem.
#include <string>
#include <bitset>
#include <math.h>
#include <queue>
#include <stack>
#include <set>
#include <map>
 
typedef long long ll;
typedef long double ld;
 
const ll MOD = 1e9 + 7, INF = 1e18 + 1;
 
using namespace std;

int n, k, u[1000], p[1000];
int d[1000][1000], t;

vector <int> g[1000];

struct chart
{
	vector <int> price;
} a[100];

bool kuhn (int x)
{
	if (u[x]) return false;
	u[x] = 1;

	for (int to : g[x])
		if (p[to] == -1 || kuhn (p[to]))
		{
			p[to] = x;
			return true;
		}

	return false;
}

bool under (chart a, chart b)
{
	for (int i = 0; i < k; i++)
		if (a.price[i] <= b.price[i]) return false;
	return true;
}

int main ()
{
	freopen ("C-small-practice.in", "r", stdin);
	freopen ("C-small-practice.out", "w", stdout);

	cin >> t;

	for (int f = 1; f <= t; f++)
	{
		memset (d, 0, sizeof (d));

		for (int i = 0; i < n; i++)
		{
			g[i].clear ();
			a[i].price.clear ();
		}

		cin >> n >> k;

		for (int i = 0; i < n; i++)
			for (int j = 0; j < k; j++)
			{
				int x;

				scanf ("%d", &x);

				a[i].price.push_back (x);
			}

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (under (a[i], a[j]))
					d[i][j] = 1;

		int r = 0;

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (d[i][j]) g[i].push_back (j);

		memset (p, -1, sizeof (p));

		for (int i = 0; i < n; i++)
		{
			memset (u, 0, sizeof (u));
			if (kuhn (i)) r++;
		}

		printf ("Case #%d: %d\n", f, n - r);
	}
}
