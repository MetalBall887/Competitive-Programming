#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <bitset>
//d_help[i][j] = the minimal cost of delivering gold for mines in a segment [i..j] if only one del. point 
//is used. The best point to place a delivering point in is where (the sum of mines' weights on the right) - (sum on the left)
//is minimum >= 0. From this greedy idea it can be seen that a "good" del.point moves to the right as j increases, so
//we can ise a two-pointer method to find this point for each j for a fixed i complexity: O(N^2).
//After this a dp optimisation trick named D&C optimisation is used, because opt[i][j] <= opt[i][j + 1]
//Proof: if there is a mine that has two del.points on both sides and belongs to the left one, then it's
//closer to the left point and after incrementing j the right point can only move to the right which makes it
//only further from our mine while the distance to the left delivering point doesn't change
#include <queue>
#include <math.h>
#include <stack>
#include <vector>
#include <string.h>

typedef long long ll;
 
const ll MOD = 1e9 + 7, INF = 1e18 + 1;
 
using namespace std;

struct mine
{
	ll x, w;
} a[5000];

ll d_help[5000][5000], d[5000][5000], n, k;

ll count (ll i, ll k, ll j)
{
	return d[i-1][k] + d_help[k + 1][j];
}

void Rec (ll k, ll l, ll r, ll optl, ll optr)
{
	if (l > r) return;

	ll mn = optl;

	ll mid = (l + r) / 2;

	for (ll i = optl; i <= min (mid - 1, optr); i++)
	{
		if (count (k, i, mid) < count (k, mn, mid)) mn = i;
	}

	d[k][mid] = count (k, mn, mid);

	Rec (k, l, mid - 1, optl, mn);
	Rec (k, mid + 1, r, mn, optr);
}

int main ()
{
	cin >> n >> k;

	for (ll i = 0; i < n; i++)
	{
		scanf ("%lld%lld", &a[i].x, &a[i].w);
	}

	for (ll i = 0; i < n; i++)
	{
		ll center = i, p_left = a[i].w, p_right = 0, sum = 0;
		for (ll j = i + 1; j < n; j++)
		{
			p_right += a[j].w;
			sum += a[j].w * (a[j].x - a[center].x);

			while (center < j && p_left < p_right)
			{
				sum += (a[center + 1].x - a[center].x) * (p_left - p_right);
				p_right -= a[center + 1].w;
				p_left += a[center + 1].w;
				center++;
			}

			d_help[i][j] = sum;
		}
	}

	for (ll i = 0; i < n; i++)
		d[0][i] = d_help[0][i];

	for (ll i = 1; i < k; i++)
		Rec (i, 0, n - 1, 0, n - 1);

	cout << d[k-1][n-1];
}
