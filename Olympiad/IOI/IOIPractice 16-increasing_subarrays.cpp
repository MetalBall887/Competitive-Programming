#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
//let a be original array and b be increasing array.
//Let's solve the problem for fixed l. Let r > l. Then b[r] must be  equal to maximal value on a[l;r] to get the 
//minimal number of changes. For example, for 2 1 4 3 5 the best monotonic array will be 2 2 4 4 5 and with increasing of
//right border no elements in array b will be changed, only added. So we can compute b[l:] to the end of b
//and first k elements of it will be the needed subarray b[l;l+k-1]. So with decreasing of l we have to add elements to the 
//front. After that some first elements in b will be equal to our new value. It can be implemented with segment tree with
//range updates. Then, for each l we have to find the leftmost r for which the cost of transforming a[l:r] to b[l:r] will
//exceed M. This cost is increasing with increasing r, so we can apply binary search in O(nlog^2n) or parallel binary
//search in O(nlogn).
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

ll n, m, a[1000000], st[1000000], ptr;
 
struct LazySeg
{
	ll t[4000000], t_lazy[4000000], sm[4000000], start;

	void push (ll node, ll l, ll r)
	{
		if (t_lazy[node] == -1) return;

		t[node] = (r - l + 1) * t_lazy[node];

		if (node < start)
		{
			t_lazy[2 * node] = t_lazy[node];
			t_lazy[2 * node + 1] = t_lazy[node];
		}

		t_lazy[node] = -1;
	}

	void build (ll n)
	{
		start = 1;
		while (start < n) start <<= 1;
	}

	void update (ll node, ll tl, ll tr, ll l, ll r, ll d)
	{
		push (node, tl, tr);

		if (r < tl || tr < l) return;

		if (l <= tl && tr <= r)
		{
			t_lazy[node] = d;
			push (node, tl, tr);
			return;
		}

		ll tm = (tl + tr) / 2;

		update (2 * node, tl, tm, l, r, d);
		update (2 * node + 1, tm + 1, tr, l, r, d);

		t[node] = t[2 * node] + t[2 * node + 1];
	}

	void change_sm (ll x, ll d)
	{
		x += start;

		while (x)
		{
			sm[x] += d;
			x >>= 1;
		}
	}

	ll order_stat (ll node, ll tl, ll tr, ll x)
	{
		push (node, tl, tr);
		if (node >= start) return min (n, node - start);

		push (2 * node, tl, (tl + tr) / 2);

		if (t[2 * node] - sm[2 * node] > x) return order_stat (2 * node, tl, (tl + tr) / 2, x);
		else return order_stat (2 * node + 1, (tl + tr) / 2 + 1, tr, x - t[2 * node] + sm[2 * node]);
	}
} t;

int main ()
{
	cin >> n >> m;

	for (ll i = 0; i < n; i++)
	{
		scanf ("%lld", &a[i]);
	}

	t.build (n);

	ll ans = 0;

	for (ll i = n - 1; i >= 0; i--)
	{
		t.change_sm (i, a[i]);

		while (ptr && a[st[ptr-1]] < a[i]) ptr--;

		if (!ptr) t.update (1, 0, t.start - 1, i, n - 1, a[i]);
		else t.update (1, 0, t.start - 1, i, st[ptr-1] - 1, a[i]);

		st[ptr] = i;
		ptr++;

		ans += (t.order_stat (1, 0, t.start - 1, m) - i);
	}

	cout << ans;
}
