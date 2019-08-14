#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <vector>
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

ll k, n, g_min = INF, ptr = 0, a[100];

map < pair <int, int>, ll> dp[20][20];

ll Rec (int l, int r, ll xl, ll xr)
{
	if (l == r - 1) return 0;

	if (dp[l][r].find ({xl, xr}) != dp[l][r].end ()) return dp[l][r][make_pair (xl, xr)];

	ll mn = INF;

	for (int i = l + 1; i < r; i++)
		mn = min (mn, Rec (l, i, xl, xl + xr) + Rec (i, r, xl + xr, xr) + a[i] * (xl + xr));

	return dp[l][r][make_pair (xl, xr)] = mn;
}

int main ()
{
	cin >> n;

	for (int i = 0; i < n; i++)
		scanf ("%lld", &a[i]);

	cout << Rec (0, n - 1, 1, 1) + a[0] + a[n-1];
}
