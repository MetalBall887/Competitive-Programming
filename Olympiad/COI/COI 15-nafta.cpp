#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <bitset>
//To begin with, we don't need two dimensions. For each pool we should know its leftmostc (l) and rightmost cells (r) 
//and its capacity (sum). Let d[i][j] be the best outcome after placing i drills in pools with r <= j, C[i][j] - the outcome
//of one drill placed in i for the same set of pools. Then d[i][j] = max C[k][j] + d[i-1][k-1] for each k, because if
//for some pool k <= r, then: a)it's not available for drill in k -> not available for any other to the left, b)it's already
//drained by the drill on k. To apply D&C dp optimisation, we need to prove that if opt[i][j] is the leftmost column to 
//optimally place a drill, opt[i][j] <= opt[i][j+1]. Then let's suppose reversed. if m1 = opt[i][j], m2 = opt[i][j+1], 
//m1 is optimal again only when the new pool is added and (let S be its capacity) d[i-1][m1-1] + C[m1][j] + S >=
//>= d[i-1][m2-1] + C[m2][j] + S (since m2 > m1 and if a pool appeared for m1, its rightmost end is on j + 1, then 
//m1 < m2 <= j + 1). After substracting S we get a contradiction. So opt[i][j] <= opt[i][j+1] and we can use D&C dp optimisation.
#include <queue>
#include <math.h>
#include <stack>
#include <vector>
#include <string.h>
 
typedef long long ll;
typedef long double ld;
 
const ll MOD = 2004, INF = 1e18 + 1;
 
using namespace std;

int C[2002][2002], d[2002][2002];

int r, s, u[2002][2002];

char a[2002][2002];

struct BIT
{
	int t[10000];

	void update (int x, int d)
	{
		for (; x <= s; x = (x | (x + 1)))
			t[x] += d;
	}

	int get (int r)
	{
		int sum = 0;

		for (;r >= 0; r = (r & (r + 1)) - 1)
			sum += t[r];
		return sum;
	}

	int get (int l, int r)
	{
		return get (r) - get (l - 1);
	}
} t;

struct pool
{
	int l, r, sum;

	void merge (const pool& b)
	{
		sum += b.sum;
		l = min (l, b.l);
		r = max (r, b.r);
	}

	bool operator< (const pool& b) const
	{
		return r < b.r;
	}
};

vector <pool> v;

pool dfs (int x, int y)
{
	u[x][y] = 1;
	pool ans = {y, y, a[x][y] - '0'};

	if (x && a[x-1][y] != '.' && !u[x-1][y]) ans.merge (dfs (x - 1, y));
	if (y && a[x][y-1] != '.' && !u[x][y-1]) ans.merge (dfs (x, y - 1));
	if (x < r - 1 && a[x+1][y] != '.' && !u[x+1][y]) ans.merge (dfs (x + 1, y));
	if (y < s - 1 && a[x][y+1] != '.' && !u[x][y+1]) ans.merge (dfs (x, y + 1));

	return ans;
}

int calc (int i, int k, int j)
{
	return C[k][j] + d[i-1][k-1];
}

void Rec (int k, int l, int r, int optl, int optr)
{
	if (l > r) return;

	int m = (l + r) / 2;

	int mn = optl;

	for (int i = optl; i <= min (m, optr); i++)
		if (calc (k, mn, m) < calc (k, i, m)) mn = i;

	d[k][m] = calc (k, mn, m);

	Rec (k, l, m - 1, optl, mn);
	Rec (k, m + 1, r, mn, optr);

}

int main ()
{
	cin >> r >> s;

	for (int i = 0; i < r; i++)
		scanf ("%s", a[i]);

	for (int i = 0; i < r; i++)
		for (int j = 0; j < s; j++)
			if (!u[i][j] && a[i][j] != '.') v.push_back (dfs (i, j));

	int ptr = 0;

	sort (v.begin(), v.end());

	for (int i = 0; i < s; i++)
	{
		while (ptr < v.size () && v[ptr].r <= i)
		{
			t.update (v[ptr].l, v[ptr].sum);
			t.update (v[ptr].r + 1, -v[ptr].sum);
			ptr++;
		}

		for (int j = 0; j <= i; j++)
		{
			C[j][i] = t.get (0, j);
			d[0][i] = max (d[0][i], C[j][i]);
		}
	}


	for (int i = 1; i < s; i++)
		Rec (i, 0, s - 1, 0, s - 1);

	for (int i = 0; i < s; i++)
		printf ("%d\n", d[i][s-1]);
}
