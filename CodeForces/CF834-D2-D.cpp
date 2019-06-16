#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
//dp[i][j][k] - the answer if we had only i boxes, only k first cookies 
//and the last cookie that belong to i-1 box is j. last dimension is 'hidden', 
//we can erase it by keeping the other two while increasing k and updating on range 
//(when we're adding a cookie on an index k, we increase d[i][j] by 1 for each j last[a[k]] <= j < k). 
//So with lazy segment tree our solution can be optimised to O(NKlogN).
#include <algorithm>
#include <bitset>
#include <queue>
#include <math.h>
#include <stack>
#include <vector>
#include <string.h>
 
typedef long long ll;
 
const ll MOD = 1e9 + 7, INF = 1e18 + 1;
 
using namespace std;

int last[200000], n, k, a[100000];
 
struct LazySeg
{
	int t[200000], t_lazy[200000], start;

	void build (vector <int> v)
	{
		int n = v.size ();
		start = 1;

		while (start < n) start <<= 1;

		for (int i = start; i < start + n; i++)
			t[i] = v[i-start];

		for (int i = start - 1; i; i--)
			t[i] = max (t[2 * i], t[2 * i + 1]);
	}

	void push (int node)
	{
		t[node] += t_lazy[node];
		if (node < start)
		{
			t_lazy[2 * node] += t_lazy[node];
			t_lazy[2 * node + 1] += t_lazy[node];
		}

		t_lazy[node] = 0;
	}

	void update (int node, int l, int r, int tl, int tr, int d)
	{
		push (node);

		if (r < tl || tr < l) return;

		if (l <= tl && tr <= r)
		{
			t_lazy[node] += d;
			push (node);
		}
		else
		{
			int tm = (tl + tr) / 2;

			update (2 * node, l, r, tl, tm, d);
			update (2 * node + 1, l, r, tm + 1, tr, d);

			t[node] = max (t[2 * node], t[2 * node + 1]);
		}
	}

	int get (int node, int l, int r, int tl, int tr)
	{
		if (l > r) return 0;
		push (node);

		if (r < tl || tr < l) return 0;

		if (l <= tl && tr <= r) return t[node];

		int tm = (tl + tr) / 2;

		return max (get (2 * node, l, r, tl, tm), get (2 * node + 1, l, r, tm + 1, tr));
	}
} dp[50];

int get_all (int k, int r)
{
	return dp[k].get (1, 0, r, 0, dp[k].start - 1);
}
 
int main ()
{
	cin >> n >> k;

	set <int> s;

	vector<int> v (n);

	for (int i = 0; i < n; i++)
	{
		scanf ("%d", &a[i]);
		s.insert (a[i]);
		v[i] = s.size ();
	}

	dp[0].build (v);

	for (int j = 1; j < k; j++)
	{
		memset (last, -1, sizeof (last));
		vector <int> new_dp;

		for (int i = 0; i < n; i++)
		{
			dp[j-1].update (1, last[a[i]], i - 1, 0, dp[j-1].start - 1, 1);
			new_dp.push_back (get_all (j - 1, i));
			last[a[i]] = i;
		}

		dp[j].build (new_dp);
	}

	cout << get_all (k - 1, n - 1);
}
