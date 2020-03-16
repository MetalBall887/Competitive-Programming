#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include <set>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <ctime>
#include <map>
#include <queue>
#include <bitset>
//Let's simulate the behaviour of the flood. Each turn it takes all walls that share a side with it and, if it shares one side
//breakes it, otherwise leaves it untouched and will not break it in further turns. Such "outer" walls can be found by one
//dfs in graph corresponding to the city and each wall after contacting the water will either be broken or "frozen", which 
//means will not participate in further turns.
 
using namespace std;
 
const long long INF = 1e9 + 1, MOD = 998244353;
 
typedef long long ll;
 
struct point
{
	int x, y, ind;
	int l[4], e[4];
 
	bool operator < (const point& b) const
	{
		return (x == b.x ? y < b.y : x < b.x);
	}
} a[200000];
 
struct edge
{
	int x, y, ind;
 
	bool operator < (const edge& b) const
	{
		return ind < b.ind;
	}
 
} b[400000];
 
int degree[200000], n, w;
 
set <edge> to_erase, ans;
set <point> s;
 
void ccw (int x)
{
	int f = x;
	int pos = 2;
 
	do
	{
		int new_pos = (pos + 1) % 4;
 
		while (a[f].l[new_pos] == -1 || !degree[a[f].l[new_pos]])
		{
			new_pos--;
			if (new_pos < 0) new_pos = 3;
		}
 
		pos = new_pos;
 
		edge k = b[a[f].e[pos]];
 
		if (to_erase.find (k) == to_erase.end ()) to_erase.insert (k);
		else ans.insert (k);
 
		f = a[f].l[pos];
	}
	while (f != x);
}
 
int main ()
{
	cin >> n;
 
	for (int i = 0; i < n; i++)
	{
		int x, y;
		scanf ("%d%d", &x, &y);
		a[i] = {x, y, i, -1, -1, -1, -1, -1, -1, -1, -1};
	}
 
	cin >> w;
 
	for (int i = 0; i < w; i++)
	{
		int x, y;
 
		scanf ("%d%d", &x, &y);
		x--;
		y--;
 
		b[i] = {x, y, i};
 
		if (x > y) swap (x, y);
 
		degree[x]++;
		degree[y]++;
 
		if (a[x].x == a[y].x)
		{
			if (a[x].y > a[y].y)
			{
				a[x].l[2] = y;
				a[x].e[2] = i;
				a[y].l[0] = x;
				a[y].e[0] = i;
			}
			else
			{
				a[x].l[0] = y;
				a[x].e[0] = i;
				a[y].l[2] = x;
				a[y].e[2] = i;
			}
		}
		else
		{
			if (a[x].x > a[y].x)
			{
				a[x].l[1] = y;
				a[x].e[1] = i;
				a[y].l[3] = x;
				a[y].e[3] = i;
			}
			else
			{
				a[x].l[3] = y;
				a[x].e[3] = i;
				a[y].l[1] = x;
				a[y].e[1] = i;
			}
		}
	}
 
	for (int i = 0; i < n; i++)
		if (degree[i]) s.insert (a[i]);
 
	while (!s.empty ())
	{
		point corner = *s.rbegin ();
		//cout << endl;
 
		to_erase.clear ();
 
		ccw (corner.ind);
 
		for (auto e : to_erase)
		{
			//cout << a[e.x].x << ' ' << a[e.x].y << ' ' << a[e.y].x << ' ' << a[e.y].y << endl;
			degree[e.x]--;
			degree[e.y]--;
 
			if (a[e.x].x == a[e.y].x)
			{
				if (a[e.x].y > a[e.y].y)
				{
					a[e.x].l[2] = -1;
					a[e.y].l[0] = -1;
				}
				else
				{
					a[e.x].l[0] = -1;
					a[e.y].l[2] = -1;
				}
			}
			else
			{
				if (a[e.x].x > a[e.y].x)
				{
					a[e.x].l[1] = -1;
					a[e.y].l[3] = -1;
				}
				else
				{
					a[e.x].l[3] = -1;
					a[e.y].l[1] = -1;
				}
			}
 
			if (degree[e.x] == 0) s.erase (a[e.x]);
			if (degree[e.y] == 0) s.erase (a[e.y]);
		}
	}
 
	cout << ans.size () << endl;
 
	for (edge it : ans)
	{
		printf ("%d\n", it.ind + 1);
	}
}
