#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <vector>
//First, notice that there aren't many slopes we should actually consider because each line's slope can be reduced/increased
//to one where some pair of points lie on this line without changing the subsets of points he's dividing the set into.
//That means, there are only n(n-1)/2 "interesting" slopes. Next observation: for a fixed bulldozer lines' slope if we
//project all points on a line perpendicular to that slope, we get a 1D maximum subarray sum problem, which leads us to
//O(N^3) solution. To make it O(N^2logN) we have to notice that after slope changing, if changed in radial order, there 
//is just a pair of points swapping, so we have to deal changing queries on a structure in logN and get the maximal subarray
//sum in O(logN) too. Segment tree fits here. The last problem is 3+ points on one line to deal with them we can sort all swaps
//that way after all swaps those elements will just be reversed on the line.
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

ll p[1000000], to[10000], n;

struct SegTree
{
	ll t[80000][4], start;
 
	ll operator[] (const int& i)
	{
		return t[i][0];
	}
 
	void build (ll n)
	{
		start = 1;
 
		while (start < n) start <<= 1;
 
		for (ll i = 2 * start - 1; i; i--)
			merge (i);
	}
 
	void merge (ll node)
	{
		if (node >= start) 
		{
			t[node][3] = p[node - start];
			t[node][2] = max (0LL, p[node - start]);
			t[node][1] = max (0LL, p[node - start]);
			t[node][0] = max (0LL, p[node - start]);
		}
		else
		{
			t[node][3] = t[2 * node][3] + t[2 * node + 1][3];
			t[node][2] = max (t[2 * node][3] + t[2 * node + 1][2], t[2 * node][2]);
			t[node][1] = max (t[2 * node][1] + t[2 * node + 1][3], t[2 * node + 1][1]);
			t[node][0] = max (max (t[2 * node][0], t[2 * node + 1][0]), t[2 * node][1] + t[2 * node + 1][2]);
		}
	}
 
	void update (ll x, ll d)
	{
		p[x] = d;
		x += start;
 
		while (x)
		{
			merge (x);
			x /= 2;
		}
	}
} t;

struct point
{
	ll x, y, c;

	bool operator < (const point& b) const
	{
		return (y == b.y ? x < b.x : y > b.y);
	}

} a[2000];

struct fraction
{
	ll a, b;

	ll p1, p2;

	bool operator < (const fraction& d) const
	{
		if (!d.b && !b) return a < d.a;
		if (!d.b) return true;
		if (!b) return false;
		if ((a * d.b) == (b * d.a)) return make_pair (p1, p2) < make_pair (d.p1, d.p2);
		return (a * d.b) < (b * d.a);
	}

	bool operator == (const fraction& d) const
	{
		if (!b && !d.b) return true;
		if (!b || !d.b) return false;
		return (a * d.b) == (b * d.a);
	}
};

vector <fraction> d;

int main ()
{
	cin >> n;

	for (ll i = 0; i < n; i++)
		scanf ("%lld%lld%lld", &a[i].x, &a[i].y, &a[i].c);

	sort (a, a + n);

	for (ll i = 0; i < n; i++)
	{
		p[i] = a[i].c;
		to[i] = i;
	}

	for (ll i = 0; i < n; i++)
		for (ll j = i + 1; j < n; j++)
		{
			ll A = a[i].y - a[j].y;
			ll B = a[i].x - a[j].x;

			d.push_back ({-B, A, i, j});
		}

	sort (d.begin(), d.end());

	t.build (n);

	ll ans = t[1];
	
	for (ll i = 0; i < d.size ();)
	{
		if (d[i].b == 0) break;

		int k = 0;

		while (i + k < d.size () && d[i + k] == d[i])
		{
			ll l = d[i + k].p1, r = d[i + k].p2, p_l = p[to[l]], p_r = p[to[r]];

			t.update (to[r], p_l);
			t.update (to[l], p_r);
		 
			swap (to[l], to[r]);
			k++;
		}

		i += k;

		ans = max (ans, t[1]);
	}

	cout << ans;
}
