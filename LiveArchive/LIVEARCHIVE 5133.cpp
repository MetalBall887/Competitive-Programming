#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
//We can hold information about working machine in linear representation. k = g_i, 
//b = (the maximal amount of money we can get by d_i) + (r_i - p_i) - g_i * (d_i + 1), so it won't add the g_i in 
//times when we didn't have this machine. 
//So we build dynamic CHT based on these lines.
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
	ld k, b, left;
	bool is_query;

	bool operator < (const line& a) const
	{
		if (a.is_query) return left < a.left;
		return k < a.k;
	}

	ll eval (ld x)
	{
		return k * x + b;
	}
};

set <line> s;
typedef set <line> :: iterator iter;

ld intersect (line a, line b)
{
	if (a.k == b.k) return 0;

	return (a.b - b.b) / (b.k - a.k);
}

bool is_prev (iter x)
{
	return x != s.begin ();
}

bool is_next (iter x)
{
	return x != s.end () && next (x) != s.end (); 
}

bool bad (line a, line b, line c)
{
	return intersect (a, c) >= intersect (b, c);
}

void update (iter x)
{
	line a = *x;
	if (!is_prev (x)) a.left = -1e13;
	else a.left = intersect (*prev (x), a);

	s.erase (x);
	s.insert (a);
}

bool bad (iter x)
{
	return is_prev (x) && is_next (x) && bad (*prev (x), *x, *next (x));
}

void add_line (line a)
{
	auto it = s.lower_bound (a);
	if (it != s.end () && it -> k == a.k)
	{
		if (it -> b >= a.b) return;
		else s.erase (it);
	}

	s.insert (a);
	it = s.lower_bound (a);

	if (bad (it))
	{
		s.erase (it);
		return;
	}

	while (is_prev (it) && bad (prev (it))) s.erase (prev (it));
	while (is_next (it) && bad (next (it))) s.erase (next (it));

	update (it);
	if (is_next (it)) update (next (it));
}

ll get_max (ld x)
{
	line q = {0, 0, x, true};
	line ans = *(--s.lower_bound (q));
	return ans.eval (x);
}

int n, q, c, d;

struct machine
{
	ld p, r, g;
};

map < int, vector <machine> > v;
map <int, ld> dp;


int main ()
{
	int t = 0;
	while (cin >> n >> c >> d && n)
	{
		t++;
		s.clear ();
		v.clear ();
		dp.clear ();

		add_line ({0, (ld) c, 0, false});

		for (int i = 0; i < n; i++)
		{
			ld p, r, g, d;

			scanf ("%Lf%Lf%Lf%Lf", &d, &p, &r, &g);

			v[d].push_back ({p, r, g});
		}

		for (auto a : v)
		{
			dp[a.first] = get_max (a.first);

			for (auto x : a.second)
				if (dp[a.first] >= x.p)
				{
					add_line ({x.g, dp[a.first] - x.g * (a.first + 1) - x.p + x.r, 0, false});
				}
		}

		printf ("Case %d: %lld\n", t, get_max (d + 1));
	}
}
