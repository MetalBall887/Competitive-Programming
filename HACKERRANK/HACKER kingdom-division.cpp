#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
//d[i][c][t] - the number of ways to color a subtree rooted in i that way vertex i is of color c and t = 0 if it's surrounded from the bottom
//with vertices of other color and t = 1 if not.
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
ll n, d[1000000][2][2];

vector <ll> g[1000000];

void dfs (ll x, ll p)
{
	d[x][0][0] = d[x][0][1] = d[x][1][0] = d[x][1][1] = 1;

	for (ll to : g[x])
		if (to != p)
		{
			dfs (to, x);
			d[x][0][0] = d[x][0][0] * d[to][1][1] % MOD;
			d[x][0][1] = d[x][0][1] * ((d[to][1][1] + d[to][0][0] + d[to][0][1]) % MOD) % MOD;

			d[x][1][0] = d[x][1][0] * d[to][0][1] % MOD;
			d[x][1][1] = d[x][1][1] * ((d[to][0][1] + d[to][1][0] + d[to][1][1]) % MOD) % MOD;
		}

		d[x][0][1] = (d[x][0][1] + MOD - d[x][0][0]) % MOD;
		d[x][1][1] = (d[x][1][1] + MOD - d[x][1][0]) % MOD;
}

int main ()
{
	cin >> n;

	for (ll i = 0; i < n - 1; i++)
	{
		ll u, v;

		scanf ("%lld%lld", &u, &v);

		g[u-1].push_back (v - 1);
		g[v-1].push_back (u - 1);
	}

	dfs (0, -1);

	cout << (d[0][0][1] + d[0][1][1]) % MOD;
}
