#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <bitset>
//first divide all number into groups that way every pair of number 
//has a full square as product if and only if numbers belong to the same group
//d[i][j] - number of ways to create a permutation from first i groups where j adjacent 
//numbers belong to the same group
#include <queue>
#include <math.h>
#include <stack>
#include <vector>
#include <string.h>
 
typedef long long ll;
 
const ll MOD = 1e9 + 7, INF = 1e18 + 1;
 
using namespace std;

ll n, d[301][301], a[301], g[301][301], group[301], gr[301];
ll c[301][301], u[301][301], ptr, fact[301];

bool check (ll a, ll b)
{
	ll n = a * b;

	ll l = 0, r = 1e9;

	while (l < r)
	{
		ll mid = (l + r) / 2;
		if (mid * mid < n) l = mid + 1;
		else r = mid;
	}

	return (l * l == n);
}

ll qpow (ll a, ll b)
{
	ll s = 1;

	while (b)
	{
		if (b % 2) s = s * a % MOD;
		b /= 2;
		a = a * a % MOD;
	}

	return s;
}

ll C (int n, int k)
{
	if (k > n || n < 0 || k < 0) return 0;
	if (k == 0) return 1;
	if (n == k) return 1;

	if (u[n][k]) return c[n][k];
	u[n][k] = 1;

	c[n][k] = C (n - 1, k) + C (n - 1, k - 1);
	while (c[n][k] >= MOD) c[n][k] -= MOD;
	return c[n][k];
}

int main ()
{
	cin >> n;

	fact[0] = 1;

	for (int i = 1; i <= n; i++)
		fact[i] = i * fact[i-1] % MOD;

	for (int i = 0; i < n; i++)
		scanf ("%lld", &a[i]);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (i != j && check (a[i], a[j]))
				group[i] = group[j];
		}

		if (!group[i]) group[i] = ++ptr;
		gr[group[i]]++;
	}

	d[1][gr[1] - 1] = fact[gr[1]];

	ll sum = 0;

	for (int i = 2; i <= ptr; i++)
	{
		sum += gr[i-1];
		for (int j = 0; j < sum; j++)
			for (int k = 1; k <= min (gr[i], sum + 1); k++)
				for (int f = 0; f <= min (k, j); f++)
					if (d[i-1][j])
					{
						ll r = d[i-1][j];
						r = r * fact[gr[i]] % MOD * C (gr[i] - 1, k - 1) % MOD;
						r = r *  C (j, f) % MOD * C (sum + 1 - j, k - f) % MOD;
						d[i][j - f + gr[i] - k] += r;
						if (d[i][j - f + gr[i] - k] >= MOD) d[i][j - f + gr[i] - k] -= MOD;
					}
	}

	cout << d[ptr][0];
}
