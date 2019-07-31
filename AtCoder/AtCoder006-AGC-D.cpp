#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <vector>
//First of all, apply binary search. If we want to check if the top of the pyramid is >= k we replace numbers >= k with 1's
//and others with 0's. Then the answer will define the result of the check. Now we have to solve a problem for a from {0, 1}.
//Let's divide our sequence in segments of the same number. If segment's length is > 1, it is stable, because every element 
//right above this segment will have at least two elements of its color in the median zone (where we take elements
//to calculate the new one). So stable segment does not change while moving up the pyramid. Instead, unstable segments, since 
//all their nearest elements have different number, are bound to change once, where they will either change once again or become a 
//part of a nearest stable segment. So we already can simulate all our segments and the way stable ones assimilate unstable and merge in O(N^2).
//To optimise, we'll consider a stable segment blocked if all its nearest segments are stable and therefore it can't grow. Once segment becomes
//blocked, it remains blocked, because even if nearest segment will become unstable after moving borders to the middle (we're on a pyramid), 
//it'll be gone the next turn. So if we don't process unstable and blocked segments, after each segment process the number of segments decrements
//so we obtain linear amortised complexity in one check function or O(NlogN) in total.
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
 
int p[1000000], sz[1000000], n, L, R;
int a[1000000], t, dp[1000][1000], ans;
 
struct segment
{
	int l, r, v;
 
	bool blocked, stable;
} d[1000000];
 
int find (int x)
{
	if (p[x] == x) return x;
	else return p[x] = find (p[x]);
}
 
segment unblock (block& s)
{
	if ((s.l - 1 < L || d[p[s.l - 1]].stable) && (s.r + 1 > R || d[p[s.r + 1]].stable)) 
	{
		s.blocked = true;
	}
	else s.blocked = false;
}
 
void update (int a, int b, int c)
{
	a = find (a);
	b = find (b);
 
	if (a == b) return;
 
	if (sz[a] < sz[b]) swap (a, b);
 
	d[a] = {min (d[a].l, d[b].l), max (d[a].r, d[b].r), c, false, true};
 
	unblock (d[a]);
 
	p[b] = a;
	sz[a] += sz[b];
}
 
bool check (int k)
{
	vector <int> v, new_v;
 
	L = 0, R = n - 1;
 
	for (int i = 0; i < n; i++)
	{
		p[i] = i;
		sz[i] = 1;
	}
 
	for (int i = 0; i < n; i++)
	{
		if (a[i] >= k) d[i] = {i, i, 1, false, false};
		else d[i] = {i, i, 0, false, false};
		if (i && d[find (i - 1)].v == d[find (i)].v) update (i - 1, i, d[i].v);
	}

	for (int i = 0; i < n; i++)
	{
		unblock (d[find (i)]);
		if (d[find (i)].stable && (v.empty () || v.back () != find (i))) v.push_back (find (i));
	}
 
	while (L < R)
	{
		d[find (L)].l++;
 
		L++;
 
		d[find (R)].r--;
 
		R--;
 
		for (int i : v)
		{
			segment x = d[find (i)];
 
			if (x.blocked) continue;
 
			if (x.l - 1 >= L)
			{
				int to = find (x.l - 1);
				if (d[to].stable && d[to].v == x.v ||
					!d[to].stable && ((d[to].v + (L & 1)) % 2 == x.v)) update (i, to, x.v);
			}
 
			if (x.r + 1 <= R)
			{
				int to = find (x.r + 1);
				if (d[to].stable && d[to].v == x.v ||
					(!d[to].stable && ((d[to].v + (L & 1)) % 2 == x.v))) update (i, to, x.v);
			}
		}
 
		new_v.clear ();
 
		for (int i : v)
		{
			unblock (d[find (i)]);
 
			segment x = d[find (i)];
 
			if (x.blocked || !x.stable) continue;
 
			if (!new_v.empty () && new_v.back () == find (i)) continue;
 
			new_v.push_back (find (i));
		}
		v = new_v;
	}

	if (d[find (L)].stable) return d[find (L)].v;
	else return (d[find (L)].v + L) & 1;
}
 
int main ()
{
	cin >> n;
 
	n = 2 * n - 1;
	 
	for (int i = 0; i < n; i++)
	{
		scanf ("%d", &a[i]);
	}
	 
	int l = 0, r = n;

	while (l < r)
	{
		int mid = (l + r + 1) / 2;
	
		if (check (mid)) l = mid;
		else r = mid - 1;
	}

	cout << l;
}
