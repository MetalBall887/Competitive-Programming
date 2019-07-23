#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
//http://usaco.org/current/data/sol_gymnasts_platinum_feb18.html
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

vector < pair <ll, ll> > v;

ll n;

ll qpow (ll a, ll b)
{
	ll s = 1;

	while (b)
	{
		if (b & 1) s = (s * a) % MOD;
		b >>= 1;
		a = (a * a) % MOD;
	}

	return s;
}

ll Rec (ll st, ll x, ll ex, ll euler)
{
	if (st == v.size ())
	{
		if (x >= n) return 0;
		return qpow (2, x) * (long long) ((n / (x * ex)) * euler % MOD) % MOD;
	}
	else
	{
		ll s = 0;
		for (int i = 0; i < v[st].second; i++)
		{
			s += Rec (st + 1, x, ex * v[st].first, euler * (v[st].first - 1));
			if (s >= MOD) s -= MOD;
			x *= v[st].first;
		}

		s += Rec (st + 1, x, ex, euler);
		if (s >= MOD) s -= MOD;

		return s;
	}
}

int main ()
{
	freopen ("gymnasts.in", "r", stdin);
	freopen ("gymnasts.out", "w", stdout);

	cin >> n;

	ll s = n;

	for (ll i = 2; i * i <= s; i++)
	{
		while (s % i == 0)
		{
			s /= i;

			if (!v.empty () && v.back ().first == i) v[v.size () - 1].second++;
			else v.push_back ({i, 1});
		}
	}

	if (s != 1)
	{
		if (!v.empty () && v.back ().first == s) v[v.size () - 1].second++;
		else v.push_back ({s, 1});
	}

	ll ans = (Rec (0, 1, 1, 1) + (2 - n % MOD + MOD) % MOD) % MOD;

	cout << ans;
}
