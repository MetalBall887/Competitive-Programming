#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <vector>
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
 
vector <int> g[1000000], cost[1000000];
 
int tout[1000000], u[1000000], n, m, timer;
 
void topsort (int x, int c)
{
	u[x] = 1;
 
	for (int i = 0; i < g[x].size (); i++)
	{
		int to = g[x][i];
 
		if (!u[to] && cost[x][i] > c)
			topsort (to, c);
	}
 
	tout[x] = ++timer;
}
 
bool dfs (int x, int c, int p)
{
	u[x] = 1;
 
	for (int i = 0; i < g[x].size (); i++)
	{
		int to = g[x][i];
 
		if (cost[x][i] > c)
		{
			if (u[to] == 1) return false;
			if (!dfs (to, c, p)) return false;
		}
	}
 
	u[x] = 2;
 
	return true;
}
 
struct edge
{
	int u, v, c, i;
 
	bool operator < (const edge& b) const
	{
		return c < b.c;
	}
} a[1000000];
 
int main ()
{
	cin >> n >> m;
 
	for (int i = 0; i < m; i++)
	{
		int u, v, c;
 
		scanf ("%d%d%d", &u, &v, &c);
 
		a[i] = {u, v, c, i};
 
		g[u-1].push_back (v - 1);
		cost[u-1].push_back (c);
	}
 
	int l = 0, r = 1e9;
 
	while (l < r)
	{
		int mid = (l + r) / 2;
 
		bool b = true;
 
		memset (u, 0, sizeof (u));
 
		for (int i = 0; i < n; i++)
			if (!u[i] && !dfs (i, mid, i + 1)) b = false;
 
		if (!b) l = mid + 1;
		else r = mid;
	}
 
	memset (u, 0, sizeof (u));
 
	for (int i = 0; i < n; i++)
		if (!u[i]) topsort (i, l);
 
	sort (a, a + m);
 
	vector <int> v;
 
	for (int i = 0; i < m; i++)
		if (a[i].c <= l && tout[a[i].u - 1] < tout[a[i].v - 1]) 
			v.push_back (a[i].i);
 
	cout << l << ' ' << v.size () << endl;
 
	sort (v.begin(), v.end());
 
	for (int i : v)
		printf ("%d ", i + 1);
}
