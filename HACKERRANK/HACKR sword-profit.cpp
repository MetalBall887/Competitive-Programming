#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
//We can divide the problems to 2 parts: for each shop finding an optimal shop to sell all the swords and finding out how many
//swords we have to sell. For the first one we have to find minimum (j - i)*di + rj for j >= i =
//= (min j * di + rj) - i * di for j >= i. Then it's a CHT problem, where j is given in decreasing order if we go from the end. 
//Then we have a problem of finding the number of swords. We have a ci = qi - (min (j-i)*di + rj for j >= i) 
//and we want to find such 
//x >= 0 f(x) = ci*x - (ai*x + bi*x*(x+1)/2) is maximal. Then f'(x) = ci - ai - bi/2 - bi*x, so we can easily find extremum.
//Also this point is a peak of a parabola, so any other point will be lower (even 0). When the peak is < 0, take the closest 
//to it (0). So x is the number of swords to buy.
//For each shop compute those two values and summarize the profits.
#include <map>
#include <algorithm>
#include <bitset>
#include <queue>
#include <math.h>
#include <stack>
#include <vector>
#include <string.h>
 
typedef long long ll;
typedef long double ld;
 
const ll MOD = 1e9 + 7, INF = 1e18 + 1;
 
using namespace std;

struct line
{
	ll s, r;
};

vector <line> cht;
ll n;

ld intersect (line a, line b)
{
	return ld (a.r - b.r) / ld (b.s - a.s);
}

bool bad (line a, line b, line c)
{
	return intersect (a, c) >= intersect (b, c);
}

void add_line (line a)
{
	while (cht.size () >= 2 && bad (cht[cht.size () - 2], cht.back (), a))
		cht.pop_back ();
	cht.push_back (a);
}

line get_min (ll x)
{
	if (cht.size () == 1 || intersect (cht[0], cht[1]) >= x) return cht[0];

	ll l = 0, r = cht.size () - 2;

	while (l < r)
	{
		ll mid = (l + r + 1) / 2;

		if (intersect (cht[mid], cht[mid + 1]) <= (ld) x) l = mid;
		else r = mid - 1;
	}

	return cht[l + 1];
}

struct shop
{
	ll q, a, b, r, d;
} a[1000000];

ll f (ll x, shop s, ll c)
{
	return (c * x % MOD + MOD - (s.a * x % MOD + (s.b * (x * (x + 1LL) % MOD * 500000004LL % MOD)) % MOD) % MOD) % MOD;
}

int main ()
{
	cin >> n;

	for (ll i = 0; i < n; i++)
	{
		scanf ("%lld%lld%lld%lld%lld", &a[i].q, &a[i].a, &a[i].b, &a[i].r, &a[i].d);
	}

	ll sum = 0;

	for (int i = n - 1; i >= 0; i--)
	{
		add_line ({i, a[i].r});

		line optimal = get_min (a[i].d);

		ll c = a[i].q - (optimal.s - i) * a[i].d - optimal.r;
		ll der = (c - a[i].a) / a[i].b;
		c %= MOD;
		der %= MOD;

		ll ans = 0;
		if (der >= 0) ans = max (ans, f (der, a[i], c));

		sum = (ans + sum) % MOD;
	}

	printf("%lld", sum);
}
