#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <bitset>
//We can keep the information about one cyclist with two variables: k(current speed) and b. Let's define b. When we add a new 
//velocity to a cyclist in time t, we know that before t his ride distance was f_old(t) and for each x >= t it will be
//f_new(x) = v*(x-t)+f_old(t). So k = v, b = f_old(t) - v*t. Now to find a maximal value out of all lines, we have to apply 
//CHT. But the problem is, our lines don't have to be added with increasing slopes, so we have to handle it dynamically.
//We can do CHT in a set, ordered by k, add one in the middle, if belongs to the hull, then delete all segments from left and
//right that are placed below our new line. Define segment points after this.
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
		if (it -> b <= a.b) return;
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

int n, q;

line d[1000000];


int main ()
{
	cin >> n >> q;

	for (int i = 0; i < n; i++)
		add_line ({0, 0, 0, false});


	for (int i = 0; i < q; i++)
	{
		int type, c; 
		ld t, v;

		scanf ("%d", &type);

		if (type == 1)
		{
			scanf ("%Lf%d%Lf", &t, &c, &v);

			add_line ({v, d[c-1].eval (t) - t * v, 0, false});
			d[c-1] = {v, d[c-1].eval (t) - t * v, 0, false};
		}
		else
		{
			scanf ("%Lf", &t);

			printf ("%lld\n", get_max (t));
		}
	}
}
