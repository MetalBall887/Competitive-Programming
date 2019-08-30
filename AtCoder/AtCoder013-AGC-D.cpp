#include <iostream>
#include <vector>
#include <stdio.h>
//d[i][j] - the number of ways to build a wall in j turns with exactly i red bricks left in the box. Since the general number of bricks is
//n, we can deduce the number of blue bricks. Now you can visualise a process of building a tower as a path through this table. To eliminate
//repetitions we can cut off all parallel paths (when they are identical if fixed to one point) by filtering only ones that touched the lowest
//border of dp table
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7;


ll n, m, d[3002][3001][2];

void add_self (ll& a, ll b)
{
	a += b;
	if (a >= MOD) a -= MOD;
}

int main ()
{
	cin >> n >> m;

	for (int i = 0; i <= n; i++)
		d[0][i][0] = 1;

	for (int i = 0; i <= m; i++)
		for (int j = 0; j <= n; j++)
		{
			int x = j, y = n - j;
			if (!x)
			{
				d[i][j][1] += d[i][j][0];
				d[i][j][0] = 0;
			}

			if (x)
			{
				if (x == 1) 
				{
					add_self (d[i + 1][j][1], d[i][j][0]);
					add_self (d[i + 1][j - 1][1], d[i][j][0]);
				}
				else 
				{
					add_self (d[i + 1][j][0], d[i][j][0]);
					add_self (d[i + 1][j - 1][0], d[i][j][0]);
				}

				add_self (d[i + 1][j][1], d[i][j][1]);
				add_self (d[i + 1][j - 1][1], d[i][j][1]);
			}

			if (y)
			{
				if (!x) 
				{
					add_self (d[i + 1][j][1], d[i][j][0]);
					add_self (d[i + 1][j + 1][1], d[i][j][0]);
				}
				else 
				{
					add_self (d[i + 1][j][0], d[i][j][0]);
					add_self (d[i + 1][j + 1][0], d[i][j][0]);
				}

				add_self (d[i + 1][j][1], d[i][j][1]);
				add_self (d[i + 1][j + 1][1], d[i][j][1]);
			}
		}

	ll ans = 0;

	for (int i = 0; i <= n; i++)
		add_self (ans, d[m][i][1]);

	cout << ans;
}
