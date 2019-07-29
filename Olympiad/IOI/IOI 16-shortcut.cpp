#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
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

ll x[1000000], to_diff[1000000], n, c;

vector <ll> d;

pair <ll, ll> diff[1000000], sum[1000000];

struct BIT
{
	ll t1[1000000], t2[1000000];

	void update (ll x, ll d)
	{
		for (; x <= n; x |= (x + 1))
		{
			t1[x] = max (t1[x], d);
			t2[x] = min (t2[x], d);
		}
	}

	pair <ll, ll> get (ll r)
	{
		ll mx = -INF, mn = INF;

		for (;r >= 0; r = (r & (r + 1)) - 1)
		{
			mx = max (mx, t1[r]);
			mn = min (mn, t2[r]);
		}

		return {mn, mx};
	}

	void clear ()
	{
		for (ll i = 0; i < n; i++)
		{
			t1[i] = -INF;
			t2[i] = INF;
		}
	}
} t_diff, t_sum;

bool check (ll k)
{
	t_diff.clear ();
	t_sum.clear ();

	vector <ll> v (n);

	ll j = 0;
	for (ll i = 0; i < n; i++)
	{
		while (j < n && diff[j].first < sum[i].first - k)
			j++;

		ll cur = sum[i].second;

		v[cur] = j;
	}

	ll min_y_plus_z = -INF, max_y_plus_z = INF;
	ll min_y_minus_z = -INF, max_y_minus_z = INF;

	for (ll i = 0; i < n; i++)
	{
		pair <ll, ll> diff_border = t_diff.get (v[i] - 1);
		pair <ll, ll> sum_border = t_sum.get (v[i] - 1);

		if (diff_border.first != INF)
		{
			min_y_plus_z = max (min_y_plus_z, sum_border.second + x[i] + d[i] - k + c);
			max_y_plus_z = min (max_y_plus_z, diff_border.first + (x[i] - d[i]) + k - c);
			min_y_minus_z = max (min_y_minus_z, x[i] + d[i] - diff_border.first - k + c);
			max_y_minus_z = min (max_y_minus_z, (x[i] - d[i]) - sum_border.second + k - c);
		}

		t_diff.update (to_diff[i], x[i] - d[i]);
		t_sum.update (to_diff[i], x[i] + d[i]);
	}

	if (min_y_plus_z > max_y_plus_z) return false;
	if (min_y_minus_z > max_y_minus_z) return false;

	int imn = n - 1, imx = n - 1;

	for (int i = 0; i < n; i++)
	{
		while (imx >= 0 && x[i] + x[imx] > max_y_plus_z) imx--;
		while (imn >= 0 && x[i] + x[imn] >= min_y_plus_z) imn--;
		if (i > imx) return 0;
		if (imn < imx)
		{
			if (x[imx] - x[i] <= max_y_minus_z && x[imx] - x[i] >= min_y_minus_z) return 1;
			if (x[imn + 1] - x[i] <= max_y_minus_z && x[imn + 1] - x[i] >= min_y_minus_z) return 1;
		}
	}

	return false;
}

ll find_shortcut (int n, vector <int> l, vector <int> d, int c)
{
	::n = n;
	::c = c;

	for (auto a : d)
		::d.push_back (a);

	for (ll i = 1; i < n; i++)
	{

		x[i] = x[i-1] + (ll) l[i-1];
	}

	for (ll i = 0; i < n; i++)
	{
		sum[i] = {x[i] + d[i], i};
		diff[i] = {x[i] - d[i], i};
	}

	sort (sum, sum + n);
	sort (diff, diff + n);

	for (ll i = 0; i < n; i++)
		to_diff[diff[i].second] = i;

	ll L = 0, R = INF;

	while (L < R)
	{
		ll mid = (L + R) / 2;
		if (check (mid)) R = mid;
		else L = mid + 1;
	}

	return L;
}

/*int main ()
{
	int n, c;

	cin >> n;

	vector <int> l (n - 1), d (n);

	for (int i = 0; i < n - 1; i++)
		scanf ("%d", &l[i]);

	for (int i = 0; i < n; i++)
		scanf ("%d", &d[i]);

	cin >> c;

	cout << find_shortcut (n, l, d, c);


	return 0;
}*/
