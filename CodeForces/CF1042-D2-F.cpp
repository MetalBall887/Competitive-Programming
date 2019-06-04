#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <stdio.h>
//In each vertex kept a queue of sets, where depicted a set by a maximal depth in it.
//In a vertex merged queues small-to-large then choose two sets with minimal depths and merged them in one.
//Overall complexity: O(Nlog^2N) with medium constant
#include <map>
#include <algorithm>
#include <bitset>
#include <queue>
#include <math.h>
#include <stack>
#include <vector>
#include <string.h>
 
typedef long long ll;
 
const ll MOD = 1e9 + 7, INF = 1e18;
 
using namespace std;

priority_queue <int> s[1000000];

int p[1000000], k, n;

vector <int> g[1000000];

void merge (priority_queue <int> & a, priority_queue <int> & b)
{
	while (!b.empty ())
	{
		a.push (b.top ());
		b.pop ();
	}
}

int dfs (int x, int par, int h)
{
	if (par != -1 && g[x].size () <= 1)
	{
		p[x] = x;
		s[p[x]].push (-h);
		return 1;
	}

	int mp = -1;
	for (int to : g[x])
		if (to != par)
		{
			dfs (to, x, h + 1);
			if (mp == -1 || s[mp].size () < s[p[to]].size ()) mp = p[to];
		}

	for (int to : g[x])
		if (to != par && p[to] != mp)
			merge (s[mp], s[p[to]]);

	p[x] = mp;

	int mn = -s[mp].top ();

	s[mp].pop ();

	while (!s[mp].empty () && (mn - s[mp].top () - 2 * h) <= k)
	{
		mn = -s[mp].top ();
		s[mp].pop ();
	}

	s[mp].push (-mn);

	if (g[x].size () == 1 && par == -1)
	{
		if (-s[mp].top () <= k) return s[mp].size ();
		else return s[mp].size () + 1;
	}

	return s[mp].size ();
}

int main ()
{
	cin >> n >> k;

	for (int i = 0; i < n - 1; i++)
	{
		int u, v;

		scanf ("%d%d", &u, &v);

		g[u-1].push_back (v - 1);
		g[v-1].push_back (u - 1);
	}

	if (n == 1) cout << 1;
	else cout << dfs (0, -1, 0);
}
