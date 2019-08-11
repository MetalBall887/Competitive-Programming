#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <vector>
//Let's start the solution from analysing Kruskal's algorithm. Front it we can get a few observations.
//1) We only have to sort edges by weight. That means, we can reorder edges with the same weight as we like.
//2) Connection between components can't deny another connection and if we can connect two components with edge at one point
//in Kruskal's cycle, we do this, so if any two vertices are connected in a graph with all edges' weight <= x, they will be
//connected in MST at that point. That means, for each point components are fixed no matter how you will reorder the edges.
//With this, we can for each query stop the Kruskal's cycle at the point where there are edges of the same size in query
//and move edges from the query to the front (observation 1). From observation 2, no matter how and how many times you 
//reordered lighter edges, it won't have any impact on existence of MST. So if we put edges with weight x first and one of
//them can't get in the MST, that means between edes in query with the same weight there is a cycle, so they all can't be the
//part of the tree. Also, if an edge doesn't connect components then there are already edges that can succesfully replace 
//this one, so putting this edge to a tree is unoptimal.
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

int p[1000000], sz[1000000], ans[1000000], q;
int u[1000000], ord[1000000];

struct edge
{
	int u, v, w, i;

	bool operator < (const edge& b) const
	{
		return w < b.w;
	}

} a[1000000];

vector <int> g[1000000];

int find (int x)
{
	if (x == p[x]) return x;
	else return p[x] = find (p[x]);
}

bool unite (int a, int b)
{
	a = find (a);
	b = find (b);

	if (a == b) return false;

	if (sz[a] < sz[b]) swap (a, b);

	p[b] = a;
	sz[a] += sz[b];

	return true;
}

int n, m;

bool cycle (int x, int p)
{
	u[x] = 1;

	for (auto to : g[x])
	{
		if (to == p) continue;
		if (u[to] == 1) return false;
		if (!u[to] && !cycle (to, x)) return false;
	}

	return true;
}

struct block
{
	vector <edge> s;
	int x, i;

	bool operator < (const block& b)
	{
		return x < b.x;
	}

} s[1000000];

int ptr;

int main ()
{
	cin >> n >> m;

	for (int i = 0; i < n; i++)
	{
		sz[i] = 1;
		p[i] = i;
	}

	for (int i = 0; i < m; i++)
	{
		scanf ("%d%d%d", &a[i].u, &a[i].v, &a[i].w);
		a[i].u--;
		a[i].v--;
		a[i].i = i;
	}

	sort (a, a + m);

	for (int i = 0; i < m; i++)
		ord[a[i].i] = i;

	cin >> q;

	for (int i = 0; i < q; i++)
	{
		int k;
		scanf ("%d", &k);

		vector <edge> v (k);

		for (int j = 0; j < k; j++)
		{
			int f;
			scanf ("%d", &f);
			v[j] = a[ord[f - 1]];
		}

		sort (v.begin (), v.end ());

		for (int j = 0; j < k; j++)
		{
			if (!j || v[j].w != v[j-1].w)
			{
				vector <edge> z;
				s[ptr++] = {z, v[j].w, i};
			}
			s[ptr-1].s.push_back (v[j]);
		}
	}

	sort (s, s + ptr);

	int j = 0;

	for (int i = 0; i < ptr; i++)
	{
		while (a[j].w < s[i].x)
		{
			unite (a[j].u, a[j].v);
			j++;
		}

		set <int> mp;

		for (edge a : s[i].s)
		{
			mp.insert (find (a.u));
			mp.insert (find (a.v));

			g[find (a.u)].push_back (find (a.v));
			g[find (a.v)].push_back (find (a.u));
		}

		for (auto a : mp)
			if (!u[a] && !cycle (a, -1)) ans[s[i].i] = 1;

		for (auto a : mp)
		{
			u[a] = 0;
			g[a].clear ();
		}
	}

	for (int i = 0; i < q; i++)
		if (ans[i]) printf ("NO\n");
		else printf ("YES\n");
}
