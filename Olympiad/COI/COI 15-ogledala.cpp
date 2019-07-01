#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <vector>
//http://hsin.hr/2015/olympiad/solutions.zip
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

unordered_map <ll, ll> d;

ll a[100000], n, m, q;

struct seg
{
	ll x, c, i;

	bool operator < (const seg& b) const
	{
		return (x == b.x ? i < b.i : x > b.x);
	}
};

vector <seg> v;

vector < pair <ll, ll> > descend (ll x)
{
	vector < pair <ll, ll> > v;

	v.push_back ({x, 1});

	ll mult_l = 1, mult_r = 1, l = (x - 1) / 2, r = x - 1 - l, n_l, n_r;

	while (l > 0 || r > 0)
	{
		if (l == r) 
		{
			v.push_back ({l, mult_l + mult_r});
			n_l = (l - 1) / 2;
			n_r = l - 1 - n_l;
			mult_l = mult_r = mult_l + mult_r;
		}
		else
		{
			if (l > 0) v.push_back ({l, mult_l});
			if (r > 0) v.push_back ({r, mult_r});
			n_l = (l - 1) / 2;
			n_r = (r - 1) / 2;

			if (2 * n_l == l - 1) 
			{
				mult_l = 2 * mult_l + mult_r;
				if (n_r == n_l) n_r = r - 1 - n_r;
			}
			else 
			{
				mult_r = mult_l + 2 * mult_r;
				if (n_r == n_l) n_l = l - 1 - n_l;
			}
		}

		l = n_l;
		r = n_r;
	}

	return v;
}

void calc (ll x, ll key)
{
	if (d.find (x) != d.end ()) return;

	if (x == key) 
	{
		d[x] = 1;
		return;
	}

	if (x < 1) 
	{
		d[x] = 0;
		return;
	}

	ll n_l = (x - 1) / 2, n_r = x - 1 - n_l;

	calc (n_l, key);
	calc (n_r, key);

	d[x] = d[n_l] + d[n_r];
}


ll ord_stat (ll x, ll c, ll len, ll l, ll r)
{
	if (len == x) return (l + r) / 2;
	ll m = (l + r) / 2;
	ll len_l = (len - 1) / 2, len_r = len - 1 - len_l;
 
	ll v_l = d[len_l], v_r = d[len_r];

	if (v_l >= c) return ord_stat (x, c, len_l, l, m - 1);
	else return ord_stat (x, c - v_l, len_r, m + 1, r);
}

int main ()
{
	cin >> m >> n >> q;

	for (ll i = 0; i < n; i++)
	{
		scanf ("%lld", &a[i]);

		auto s = descend (a[i] - (i ? a[i-1] : 0) - 1);

		for (auto k : s)
			v.push_back ({k.first, k.second, i});
	}

	auto s = descend (m - (n ? a[n-1] : 0));

	vector <seg> b;

	for (auto k : s)
		v.push_back ({k.first, k.second, n});

	sort (v.begin (), v.end ());

	for (auto a : v)
	{
		if (b.empty () || b.back ().x != a.x || b.back ().i != a.i)
			b.push_back (a);
		else b[b.size () - 1].c += a.c;
	}

	v = b;

	ll ptr = 0, sum = 0;

	for (int i = 0; i < q; i++)
	{
		ll b;
		scanf ("%lld", &b);

		if (b <= n)
		{
			printf ("%lld\n", a[b-1]);
			continue;
		}
		b -= n;
		if (sum + v[ptr].c < b)
		{
			do
			{
				sum += v[ptr].c;
				ptr++;
			}
			while (ptr != v.size () && sum + v[ptr].c < b);
		}
 
		ll l = (v[ptr].i ? a[v[ptr].i - 1] + 1 : 1), r = (v[ptr].i != n ? a[v[ptr].i] - 1 : m);
		d.clear ();
 
		calc (r - l + 1, v[ptr].x);
 
		printf ("%lld\n", ord_stat (v[ptr].x, b - sum, r - l + 1, l, r));
	}
}
