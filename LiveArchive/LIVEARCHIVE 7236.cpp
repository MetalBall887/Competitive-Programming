#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <bitset>
//f[i][j] - TED of trees where roots are vertex i from T1 and vertex j from T2. Then for these roots we have to match children
//that way outcoming TED is minimal. Notice that for some price we can take only a subset of children from vertex i by simply
//removing any other vertices and paying corresponding price. But then might happen that we need to leave a subset of children
//of vertex j. Then for children that aren't in that subset we can build specific subtrees and will eventually forget about them
//because their only purpose was to copy these children of j. Now when we can specifically exclude some children from i and j 
//we can match only some arbitrary number of pairs of children from i and j and remove/copy others, what will lead us to a matching
//problem. But since for li-th children (from the left) of i and r-ith of j works li-1 < li and ri-1 < ri, so we can apply a
//O(n^2) dp. The number of operations is O(Σi Σj di*dj) = O(Σi di * (Σj dj)) = O(Σi di * M) = O(NM) where N and M are sizes of
//T1 and T2.
#include <math.h>
#include <queue>
#include <stack>
#include <set>
#include <map>
 
typedef long long ll;
typedef long double ld;
 
const ll MOD = 1e9 + 7, INF = 1e18 + 1;
 
using namespace std;

vector <int> g[10000], v[10000];

int a[1000000], ptr, n, m, sz[1000000][2], u[1001][1001], f[1001][1001], d[1001][1001];

char c[10000][10];

string s;

int Rec (int x, int y)
{
	int ans = 0;
	if (u[x][y]) return f[x][y];
	u[x][y] = 1;

	ans = sz[x][0] - 1 + sz[y][1] - 1 + (c[x][0] != c[y][1]);



	if (g[x].size () > 0 && v[y].size () > 0)
	{
		for (int i = 1; i <= g[x].size (); i++)
			for (int j = 1; j <= v[y].size (); j++)
				Rec (g[x][i-1], v[y][j-1]);

		d[0][0] = 0;

		for (int i = 1; i <= g[x].size (); i++)
			d[i][0] = d[i-1][0] + sz[g[x][i-1]][0];

		for (int i = 1; i <= v[y].size (); i++)
			d[0][i] = d[0][i-1] + sz[v[y][i-1]][1];

		for (int i = 1; i <= g[x].size (); i++)
			for (int j = 1; j <= v[y].size (); j++)
			{
				d[i][j] = min (d[i][j-1] + sz[v[y][j-1]][1], d[i-1][j] + sz[g[x][i-1]][0]);
				d[i][j] = min (d[i][j], d[i-1][j-1] + Rec (g[x][i-1], v[y][j-1]));
			}

		ans = min (ans, d[g[x].size ()][v[y].size ()] + (c[x][0] != c[y][1]));
	}

	f[x][y] = ans;

	return ans;
}

int dfs (int x, int p, int z)
{
	sz[x][z] = 1;

	vector <int> e;

	if (z) e = v[x];
	else e = g[x];

	for (int to : e)
		if (to != p)
		{
			sz[x][z] += dfs (to, x, z);
		}

	return sz[x][z];
}

int main ()
{
	int t;
	cin >> t;

	while (t--)
	{
		for (int i = 0; i < n; i++)
		{
			g[i].clear ();
			for (int j = 0; j < m; j++)
				u[i][j] = f[i][j] = 0;
		}

		for (int i = 0; i < m; i++)
			v[i].clear ();

		n = m = 0;

		cin >> s;

		for (char k : s)
		{
			if (k == ')') ptr--;
			else if (k != '(') 
			{
				a[ptr] = n++;
				c[n-1][0] = k;
				if (ptr) g[a[ptr-1]].push_back (n - 1);
				ptr++;
			}
		}
		cin >> s;

		for (char k : s)
		{
			if (k == ')') ptr--;
			else if (k != '(') 
			{
				a[ptr] = m++;
				c[m-1][1] = k;
				if (ptr) v[a[ptr-1]].push_back (m - 1);
				ptr++;
			}
		}

		dfs (0, -1, 0);
		dfs (0, -1, 1);

		printf ("%d\n", Rec (0, 0));
	}
}
