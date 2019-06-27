#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <vector>
//We run a dp, where the state is a depiction of next 3 columns and a number of column. First, the number of states 
//may have been seen O(2^3m), but notice, that if we add rectangles from left to right, we only need the rightmost bit 
//from each row, so the number of states for a column is already O(4^m). But also we can discard all states that 
//have a local maximum, since we have no rectangles with side 1, so the number of states for each column is ~35000.
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

int er[151][10], n, m, k, d[2][2000000];

struct state
{
	int x, a[10], num;

	state (int nm, int x) : num (nm), x (x)
	{
		for (int i = 0; i < m; i++)
		{
			a[i] = (nm & 3);
			nm >>= 2;
		}
	}

	bool valid ()
	{
		if (m > 1 && a[0] > a[1]) return false;
		if (m > 1 && a[m-2] < a[m-1]) return false;

		for (int i = 1; i < m - 1; i++)
		{
			if (a[i-1] < a[i] && a[i] > a[i+1]) return false;
		}

		return true;
	}

	bool pass (int y, int sz)
	{
		if (y + sz > m || x + (5 - sz) > n) return false;
		if (sz == 2)
		{
			if (!a[y] && !a[y + 1] && !((er[x][y] | er[x][y + 1]) & 7)) return true;
		}
		else if (!a[y] && !a[y + 1] && !a[y + 2] && !((er[x][y] | er[x][y + 1] | er[x][y + 2]) & 3)) return true;

		return false;
	}

	state create (int y, int sz)
	{
		state v (0, x + 1);

		for (int i = 0; i < m; i++)
		{
			v.a[i] = a[i] + ((i >= y) && (i < y + sz) ? 5 - sz : 0);
			v.num += v.a[i] * (1 << (2 * i));
		}
		return v;
	}

	state propagate ()
	{
		state v (num, x + 1);
		v.num = 0;
		for (int i = 0; i < m; i++)
		{
			if (v.a[i]) v.a[i]--;
			v.num += v.a[i] * (1 << (2 * i));
		}

		return v;
	}
};

void relax (int nm, int l, int k)
{
	state x (nm, l);

	for (int i = 0; i < m; i++)
	{
		if (x.pass (i, 2))
		{
			state to = x.create (i, 2);

			d[k][to.num] = max (d[k][to.num], d[k][x.num] + 1);
		}

		if (x.pass (i, 3))
		{
			state to = x.create (i, 3);

			d[k][to.num] = max (d[k][to.num], d[k][x.num] + 1);
		}
	}
}

vector<int> valid;

int a[150][10];

int main ()
{
	m = 10;
	for (int i = 0; i < (1 << 20); i++)
	{
		state k (i, 0);
		if (k.valid ()) valid.push_back (i);
	}

	int D;

	cin >> D;

	while (D--)
	{
		cin >> n >> m >> k;

		memset (er, 0, sizeof (er));
		memset (a, 0, sizeof (a));
		memset (d, 0, sizeof (d));

		for (int i = 0; i < k; i++)
		{
			int u, v;
			scanf ("%d%d", &u, &v);
			a[u-1][v-1] = 1;
		}

		for (int i = 0; i < m; i++)
			er[n][i] = (1 << 4) - 1;

		for (int i = n - 1; i >= 0; i--)
			for (int j = 0; j < m; j++)
				er[i][j] = ((er[i + 1][j] * 2) + a[i][j]) % 16;

		int ans = 0;

		d[0][0] = 1;

		for (int i = 0; i < n; i++)
		{
			k = i & 1;
			for (int j : valid)
				if (d[k][j])
				{
					ans = max (ans, d[k][j]);
					relax (j, i, k);
				}

			for (int j : valid)
				if (d[k][j])
				{
					state a (j, i);
					state b = a.propagate ();
					d[!k][b.num] = max (d[!k][b.num], d[k][a.num]);
					d[k][j] = 0;
				}
		}

		cout << ans - 1 << endl;
	}
}
