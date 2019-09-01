#include <iostream>
#include <vector>
#include <stdio.h>
//d[i][j] - the number of versions of permutation where ai > aj. The sum of versions is 2^q. 
//We can maintain this 
//table by adding new swaps, because for x and y going to swap in half of possibilities d[x][j] will change into d[y][j]. 
//Each swap changes O(n) pairs, so the complexity is O(nq).
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7;

ll a[3000], n, q, pw, inv2;

ll qpow (ll a, ll b)
{
	ll s = 1;

	while (b)
	{
		if (b & 1) s = s * a % MOD;
		b >>= 1;
		a = a * a % MOD;
	}

	return s;
}

ll d[3000][3000];

ll div2 (ll a)
{
	return {a * inv2 % MOD};
}

ll sum (ll a, ll b)
{
	return {(a + b) % MOD};
}

int main ()
{
	cin >> n >> q;

	pw = qpow (2, q);
	inv2 = qpow (2, MOD - 2);


	for (int i = 0; i < n; i++)
		scanf ("%lld", &a[i]);

	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			if (a[i] > a[j]) {
				d[i][j] = pw;
			}
			else if (a[i] < a[j]) {
				d[j][i] = pw;
			}

	for (int i = 0; i < q; i++) {
		int x, y;
		scanf ("%d%d", &x, &y);
		x--;
		y--;

		for (int j = 0; j < n; j++)
			if (j != x && j != y) {

				auto xj = d[x][j], yj = d[y][j], jx = d[j][x], jy = d[j][y];

				d[x][j] = div2 (sum (xj, yj));
				d[y][j] = div2 (sum (xj, yj));
				d[j][x] = div2 (sum (jx, jy));
				d[j][y] = div2 (sum (jx, jy));
			}

		auto xy = d[x][y], yx = d[y][x];

		d[x][y] = div2 (sum (xy, yx));
		d[y][x] = div2 (sum (xy, yx));
	}

	ll ans = 0;

	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
		{
			ans += d[i][j];
			if (ans >= MOD) ans -= MOD;
		}

	cout << ans;
}
