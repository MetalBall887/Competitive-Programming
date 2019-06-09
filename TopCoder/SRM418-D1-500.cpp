#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
#include <algorithm>
//create a graph where ther is an edge (u, v) when u and v want the same mark
//then find an independent set with maximum node weight
//since max.degree is 2, we have only simple cycles and trees with max.degree 2
//so IS can be found with polynomial complexity
#include <bitset>
#include <queue>
#include <math.h>
#include <stack>
#include <vector>
#include <string.h>
 
typedef long long ll;
 
const ll MOD = 1e9 + 7, INF = 1e18 + 1;
 
using namespace std;

class StampsCollection
{
public:
	vector <int> g[1000], c[1000], tmp;
	int u[1000];

	int cycle (int x, int p, int color)
	{
		u[x] = 1;
		int s = g[x].size ();

		c[color].push_back (x);

		for (int to : g[x])
			if (to != p && !u[to])
				s = min (s, cycle (to, x, color));
		
		return s;
	}

	int find_root (int x, int p)
	{
		if (g[x].size () <= 1) return x;

		if (g[x][0] == p) return find_root (g[x][1], x);
		else return find_root (g[x][0], x);
	}

	void dfs (int x, int p)
	{
		tmp.push_back (x);

		for (int to : g[x])
			if (to != p) dfs (to, x);
	}

	vector <int> & order (int x)
	{
		tmp.clear ();
		int r = find_root (x, -1);

		dfs (r, -1);

		return tmp;
	}

	pair <int, int> process (string a)
	{
		pair <int, int> s;

		if (a.size () == 1) return make_pair (a[0] - '0', -1);
		if (a.size () == 2) return make_pair ((a[0] - '0') * 10 + a[1] - '0', -1);
		if (a.size () == 3) return make_pair (a[0] - '0', a[2] - '0');
		else 
		{
			if (a[1] != ' ') s.first = (a[0] - '0') * 10 + a[1] - '0';
			else s.first = a[0] - '0';
			if (a[a.length () - 2] != ' ') 
				s.second = (a[a.length () - 2] - '0') * 10 + a[a.length () - 1] - '0';
			else s.second = a[a.length () - 1] - '0';

			return s;
		}
	}

	int sell (int n, vector <string> demand, vector <int> price)
	{
		n++;
		vector <int> offer (100, -1);
		for (int i = 0; i < demand.size (); i++)
		{
			auto b = process (demand[i]);
			
			if (offer[b.first] == -1) offer[b.first] = i;
			else
			{
				g[offer[b.first]].push_back (i);
				g[i].push_back (offer[b.first]);
			}

			if (b.second == -1) continue;
			if (offer[b.second] == -1) offer[b.second] = i;
			else if (offer[b.first] != offer[b.second])
			{
				g[offer[b.second]].push_back (i);
				g[i].push_back (offer[b.second]);
			}
		}

		int color = 0, ans = 0;

		for (int i = 0; i < demand.size (); i++)
			if (!u[i])
			{
				int mx = 0;
				if (cycle (i, -1, ++color) == 2)
				{
					vector<int> & v = c[color];
					vector<int> d1[2], d2[2];
					for (int h = 0; h < 2; h++) 
					{
						d1[h].resize (100);
						d2[h].resize (100);
					}

					d2[1][0] = price[v[0]];
					
					for (int k = 1; k < v.size (); k++)
					{
						d1[0][k] = max (d1[0][k-1], d1[1][k-1]);
						d1[1][k] = d1[0][k-1] + price[v[k]];
						
						d2[0][k] = max (d2[0][k-1], d2[1][k-1]);
						d2[1][k] = d2[0][k-1] + price[v[k]];
					}
					
					mx = max (max (d1[0][v.size () - 1], d1[1][v.size () - 1]), d2[0][v.size () - 1]);
				}
				else
				{
					vector<int> & v = order (i);
					vector<int> d[2];

					d[0].resize (100);
					d[1].resize (100);
					d[1][0] = price[v[0]];

					for (int k = 1; k < v.size (); k++)
					{
						d[0][k] = max (d[0][k-1], d[1][k-1]);
						d[1][k] = d[0][k-1] + price[v[k]];
					}

					mx = max (d[0][v.size () - 1], d[1][v.size () - 1]);
				}

				ans += mx;
			}

		return ans;
	}
};
