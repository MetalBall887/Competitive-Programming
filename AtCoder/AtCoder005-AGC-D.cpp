#include <iostream>
#include <vector>
#include <stdio.h>
//http://agc005.contest.atcoder.jp/data/agc/005/editorial.pdf
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 924844033;
 
ll n, k, cnt;
string s;

ll d[4000][4001][2], a[4000], f[4000];
int main ()
{
	cin >> n >> k;

	for (int i = 0; i < k; i++)
	{
		for (int j = i; j < n; j += k)
			a[cnt++] = (j != i);

		for (int j = i; j < n; j += k)
			a[cnt++] = (j != i);
	}

	d[0][0][0] = 1;
	d[0][0][1] = 1;

	for (ll i = 1; i < cnt; i++)
		for (ll j = 0; j <= cnt; j++)
		{
			d[i][j][0] = d[i-1][j][0];
			if (a[i] && j) d[i][j][0] += d[i-1][j-1][1];
			if (d[i][j][0] >= MOD) d[i][j][0] -= MOD;

			d[i][j][1] = d[i-1][j][0];
		}

	f[0] = 1;

	for (ll i = 1; i <= n; i++)
		f[i] = (i * f[i-1]) % MOD;

	ll ans = 0;
	for (ll i = 0; i <= n; i++)
	{
		ll t = f[n-i] * d[cnt-1][i][0] % MOD;
		if (i & 1) t = -t;
		ans += MOD + t;
		ans %= MOD;
	}

	cout << ans;

}
