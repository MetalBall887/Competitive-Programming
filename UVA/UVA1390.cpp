#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
//the state of dp is set of components, where one component is depicted with the number of elements
//in it. the number of different states with <= 30 nodes is not that big. Then we start dfs from the starting state
//where dfs (x) is the answer to the problem from state x
#include <algorithm>
#include <bitset>
#include <queue>
#include <math.h>
#include <stack>
#include <vector>
#include <string.h>
 
typedef long long ll;
 
const ll MOD = 1e9 + 7, INF = 1e18 + 1;
 
using namespace std;

map < vector <double>, double > d_sum;

int u[100], n, m;

vector <int> g[100];

int flood_fill (int x)
{
	u[x] = 1;

	int s = 1;

	for (int to : g[x])
		if (!u[to]) s += flood_fill (to);

	return s;
}


double dfs (vector <double> a)
{
	if (a.size () == 1) return 0;

	if (d_sum.find (a) != d_sum.end ()) return d_sum[a];

	//stat - the number of edges don't that change the state, prob - the probability
	//that our state will change to the current new one
  	//let x = current state, to = new state,
	//d[x] = sum of ((d[to] + 1) * prob) for each to + stat * (d[x] + 1)
	//d[x] = sum (d[to] * prob) + d[x] * stat + 1 
	//(since sum of prob for every to + stat = 1)
	//d[x] = (sum (d[to] * prob) + 1) / (1 - stat)
	
	double stat = 0;

	for (int i = 0; i < a.size (); i++)
	{
		stat += a[i] * (a[i] - 1) / 2;
	}

	double all = n * (n - 1) / 2;

	double sum_change = 0;

	for (int i = 0; i < a.size (); i++)
		for (int j = i + 1; j < a.size (); j++)
		{
			vector <double> new_st;

			for (int k = 0; k < a.size (); k++)
				if (k != i && k != j)
					new_st.push_back (a[k]);

			new_st.push_back (a[i] + a[j]);

			sort (new_st.begin(), new_st.end());

			double prob = (double) a[i] * (double) a[j] / all;

			sum_change += prob * dfs (new_st);
		}

	d_sum[a] = (sum_change + 1) / (1 - stat / all);

	return d_sum[a];
}

int main ()
{
	while (cin >> n >> m)
	{
		for (int i = 0; i < m; i++)
		{
			int u, v;

			scanf ("%d%d", &u, &v);

			g[u-1].push_back (v - 1);
			g[v-1].push_back (u - 1);
		}

		vector <double> start;

		for (int i = 0; i < n; i++)
			if (!u[i])
				start.push_back (flood_fill (i));

		sort (start.begin(), start.end());

		printf ("%.6lf\n", dfs (start));

		d_sum.clear ();

		for (int i = 0; i < n; i++)
		{
			g[i].clear ();
			u[i] = 0;
		}
	}
}
