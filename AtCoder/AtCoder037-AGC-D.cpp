#include <iostream>
#include <vector>
//https://img.atcoder.jp/agc037/editorial.pdf
//slower on that Hall's Marriage Theorem. We know that for each vertex-row there are m candidates on vertex-color. So if we take
//some subsets of vertices-rows W, there would be |W|m candidates on vertices-colors. From Dirichlet's principle, if there are
//|W|m rabbits and one cage can contain max. m rabbits, then the number of cages is at least |W|. That means, they generally have
//at least |W| neighbouring vertices which makes Hall's Marriage rule work.
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int p[1000000], u[100], n, m;

vector <int> g[1000000];

int v[100][100], a[100][100];

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

int main ()
{
	cin >> n >> m;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf ("%d", &a[i][j]);

	for (int k = 0; k < m; k++)
	{
		memset (p, -1, sizeof (p));

		for (int i = 0; i < n; i++)
		{
			g[i].clear ();
			for (int j = k; j < m; j++)
			{
				int d = (a[i][j] - 1) / m;
				g[i].push_back (d);
			}
		}

		for (int i = 0; i < n; i++)
		{
			kuhn (i);
			memset (u, 0, sizeof (u));
		}

		vector <int> to (n);

		for (int i = 0; i < n; i++)
			to[p[i]] = i;

		for (int i = 0; i < n; i++)
			for (int j = k; j < m; j++)
			{
				if ((a[i][j] - 1) / m == to[i])
				{
					swap (a[i][k], a[i][j]);
					break;
				}
			}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			printf ("%d ", a[i][j]);
		putchar ('\n');
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			v[(a[i][j] - 1) / m][j] = a[i][j];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			printf ("%d ", v[i][j]);
		putchar ('\n');
	}
}
