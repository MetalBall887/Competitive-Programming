#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
//first observation: if we remove all fields that can be fully contained in some another fields
//(we can just put them in whatever group the field that has both dimensions bigger, so it will be free) and then sort
//increasing the height, the width will be decreasing. second observation: in this ordering it is only optimal to 
//group fields in segments, because if we take any two fields in one group, we can take all fields between them for free.
//so for dp[i] for first i element we need to find such j <= i, that c = w[j] * h[i] + dp[j-1] = max. 
//We can use a Convex Hull Trick for this.
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
 
int n, ptr, w, h;

struct line
{
	ll k, b;

	ll eval (ld x)
	{
		return k * x + b;
	}
};

double intersect (line a, line b)
{
	return double (b.b - a.b) / double (a.k - b.k);
}

vector <line> cht, lines;

void add (line a)
{
	while (cht.size () >= 2 && intersect (cht[ptr - 2], a) <= intersect (cht[ptr - 2], cht[ptr - 1]))
	{
		cht.pop_back ();
		ptr--;
	}

	cht.push_back (a);
	ptr++;
}

ll find_min (int x)
{
	if (ptr == 1 || (double) x <= intersect (cht[0], cht[1])) return cht[0].eval (x);

	int l = 0, r = ptr - 2;

	while (l < r)
	{
		int mid = (l + r + 1) / 2;

		if (intersect (cht[mid], cht[mid + 1]) <= (double) x) l = mid;
		else r = mid - 1;
	}

	return cht[l + 1].eval (x);
}

vector < pair <int, int> > v, d;

ll dp[1000000];

int main ()
{
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		int w, h;

		scanf ("%d%d", &w, &h);

		v.emplace_back (w, h);
	}

	sort (v.begin(), v.end());

	int mx = 0;

	for (int i = n - 1; i >= 0; i--)
		if (v[i].second > mx)
		{
			mx = v[i].second;
			d.push_back (v[i]);
		}

	reverse (d.begin(), d.end());

	line a = {d[0].second, 0};

	add (a);

	dp[0] = find_min (d[0].first);

	for (int i = 1; i < d.size (); i++)
	{
		a = {d[i].second, dp[i-1]};
		add (a);
		dp[i] = find_min (d[i].first);
	}

	cout << dp[d.size () - 1];
}
