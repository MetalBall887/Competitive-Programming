#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <bitset>
#include <queue>
//The main idea is that we will use at most one (one or zero) car on each path from one key district to another.
//So we have a model, where for each path between two key districts we can use 1 car or not use cars ar all, 
//we can use a car only once and each path should be used. We can build a bipartite graph according to this description
//and find a minimum cost flow. We can find a shortest path between key districts using a car by 2d dp.
#include <math.h>
#include <stack>
#include <vector>
#include <string.h>

typedef long long ll;
 
const ll MOD = 1e9 + 7, INF = 1e18 + 1;
 
using namespace std;

class SlimeXGrandSlimeAuto
{
	int g[200][200], S = 0, T, f[200][200];

	int find_path ()
	{
		vector <int> d (T + 1, 1e9), p (T + 1), u (T + 1);

		d[0] = 0;
		u[i] = 1;

		for (int k = 0; k <= T; k++)
			for (int i = 0; i <= T; i++)
				for (int j = 0; j <= T; j++)
					if (u[i] && f[i][j] && d[j] > d[i] + g[i][j])
					{
						p[j] = i;
						d[j] = d[i] + g[i][j];
					}

		for (int i = 0; i < )

		if (!u[T]) return -69;

		int x = T, cap = 1e9, cost = 0;

		while (x != S)
		{
			cap = min (cap, f[p[x]][x]);
			x = p[x];
		}

		x = T;

		while (x != S)
		{
			f[p[x]][x] -= cap;
			f[x][p[x]] += cap;
			cost += g[p[x]][x] * cap;
			x = p[x];
		}

		return cost;
	}

	int flow ()
	{
		int ans = 0, a;

		while ((a = find_path ()) != -69)
			ans += a;

		return ans;
	}

	int travel (vector <int> cars, vector <int> districts, vector <string> roads, int inverseWalkSpeed, int inverseDriveSpeed)
	{
		int d[50][50], d_car[50][50][50], n = roads[0].length ();

		for (int i = 0; i < roads.size (); i++)
			for (int j = 0; j < roads[i].length (); i++)
			{
				if (roads[i][j] == '.') d[i][j] = 1e9;
				else if (isdigit (roads[i][j])) d[i][j] = 1 + roads[i][j] - '0';
				else if ('A' <= roads[i][j] && roads[i][j] <= 'Z') d[i][j] = 37 + roads[i][j] - 'A';
				else d[i][j] = 11 + roads[i][j] - 'a';
			}

		for (int i = 0; i < n; i++)
			d[i][i] = 0;

		for (int i = 0; i < 200; i++)
			for (int j = 0; j < 200; j++)
			{
				f[i][j] = 0;
				g[i][j] = 0;
			}

		for (int k = 0; k < n; i++)
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					d[i][j] = min (d[i][j], d[i][k] + d[k][j]);

		for (int k = 0; k < cars.length (); k++)
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					d_car[i][j][k] = min (d[i][j * inverseWalkSpeed], 
						d[i][cars[k]] * inverseWalkSpeed + d[cars[k]][j] * inverseDriveSpeed);


		for (int i = 0; i < cars.size (); i++)
		{
			f[0][i + 1] = 1;

			int past = 0;

			for (int j = 0; j < districts.size (); j++)
			{
				g[i + 1][cars.size () + 2 + j] = d_car[past][district[j]][i];
				f[i + 1][cars.size () + 2 + j] = 1;
				past = districts[j];
			}
		}

		f[0][cars.size () + 1] = 1e9;

		int past = 0;

		for (int j = 0; j < districts.size (); j++)
		{
			g[cars.size () + 1][cars.size () + 2 + j] = d[past][district[j]] * inverseWalkSpeed;
			f[cars.size () + 1][cars.size () + 2 + j] = 1;
			past = districts[j];
		}

		T = cars.size () + 2 + districts.size ();

		for (int j = 0; j < districts.size (); j++)
			f[cars.size () + 2 + j][T] = 1;

		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
				g[j][i] = -g[i][j];

		return flow ();
	}
}
