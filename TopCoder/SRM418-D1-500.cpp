#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
#include <algorithm>
//create a graph where ther is an edge (u, v) when u and v want the same mark
//then find a matching with maximum node weight
//since max.degree is 2, we have only simple cycles and trees with max.degree 2
//so matching can be found with polynomial complexity
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
	vector <int> g[1000], c[1000];
	int u[1000];

	bool cycle (int x, int p, int color)
	{
		if (u[x]) return true;
		u[x] = 1;

		c[color].push_back (x);

		for (int to : g[x])
			if (to != p)
				if (cycle (to, x, color)) return true;
		return false;
	}

	pair <int, int> process (string a)
	{
		pair <int, int> s;

		if (a.size () == 1) return make_pair (a[0] - '0', -1);
		if (a.size () == 1) return make_pair ((a[0] - '0') * 10 + a[1] - '0', -1);
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
		vector <int> offer (100, -1);
		for (int i = 0; i < demand.size (); i++)
		{
			auto b = process (demand[i]);
			
			cout << b.first << ' ' << b.second << endl;
			
			if (offer[b.first] == -1) offer[b.first] = i;
			else
			{
				g[offer[b.first]].push_back (i);
				g[i].push_back (offer[b.first]);
			}

			if (b.second == -1) continue;
			if (offer[b.second] == -1) offer[b.second] = i;
			else
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
				if (cycle (i, -1, ++color))
				{
					vector<int> & v = c[color];
					for (int k = 0; k < v.size (); k++)
					{
						int odd_price = 0;

						for (int j = 0; j < v.size (); j++)
							if (j % 2) odd_price += price[v[(j + k) % v.size ()]];

						mx = max (mx, odd_price);
					}
				}
				else
				{
					int odd_price = 0, even_price = 0;
					vector<int> & v = c[color];

					for (int j = 0; j < v.size (); j++)
						if (j % 2) odd_price += price[v[j]];
						else even_price += price[v[j]];

					mx = max (odd_price, even_price);
				}

				ans += mx;
			}

		return ans;
	}
};
