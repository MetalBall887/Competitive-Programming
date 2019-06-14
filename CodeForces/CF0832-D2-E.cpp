#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
//Notice that adding a string 5 times doesn't chenge anything, so we don't have to add strings
//more than 4 times. If we say that Aij is the alphabet-order number of the char j of string i
//xi is the number of times we should add the ith string and Bj is is the alphabet-order number of the char
//we need to get in the place j, we get the system of linear equations Ax=B.By remembering every change that
//should be done on a vector B, we can also speed up the algorithm.
#include <map>
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

struct operation
{
	string type;
	int a, mult, b;
};

vector <operation> ord;

int a[500][500], at[500], n, m, q, inv[6], c[500][500], u[500], rnk;

ll p_ans = 1;

char s[1000];

ll qpow (ll a, ll b)
{
	ll s = 1;

	while (b)
	{
		if (b & 1) s = s * a % MOD;
		b /= 2;
		a = a * a % MOD;
	}

	return s;
}

void gaussian_elimination ()
{
	memset (at, -1, sizeof (at));

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			if (a[j][i] && (at[i] == -1 || a[at[i]][i] < a[j][i]) && !u[j]) at[i] = j;

		if (at[i] != -1)
		{
			u[at[i]] = 1;
			int dv = a[at[i]][i];
			for (int j = 0; j < n; j++)
				a[at[i]][j] = a[at[i]][j] * inv[dv] % 5;
			ord.push_back ({"div", at[i], dv, 0});

			for (int j = 0; j < m; j++)
				if (j != at[i])
				{
					int ml = a[j][i];
					for (int k = 0; k < n; k++)
					{
						a[j][k] -= (a[at[i]][k] * ml) % 5;
						if (a[j][k] < 0) a[j][k] += 5;
					}

					ord.push_back ({"sub", j, ml, at[i]});
				}
		}
		else rnk--;
	}
}

int main ()
{
	cin >> n >> m;

	for (int i = 0; i <= 5; i++)
		inv[i] = (i * i * i) % 5;

	rnk = n;

	for (int i = 0; i < n; i++)
	{
		scanf ("%s", s);

		for (int j = 0; j < m; j++)
			c[j][i] = a[j][i] = s[j] - 'a';
	}

	gaussian_elimination ();

	p_ans = qpow (5, n - rnk);

	cin >> q;

	while (q--)
	{
		vector <int> b (m);

		int res[1000];

		scanf ("%s", s);

		for (int i = 0; i < m; i++)
			b[i] = s[i] - 'a';

		memset (res, 0, sizeof (res));

		for (auto x : ord)
		{
			if (x.type == "div") b[x.a] = b[x.a] * inv[x.mult] % 5;
			else b[x.a] = (b[x.a] + 5 - b[x.b] * x.mult % 5) % 5;
		}

		for (int i = 0; i < n; i++)
			if (at[i] != -1)
			{
				for (int j = 0; j < m; j++)
					res[j] = (res[j] + b[at[i]] * c[j][i]) % 5;
			}

		ll ans = p_ans;

		for (int i = 0; i < m; i++)
			if (s[i] != res[i] + 'a')
				ans = 0;

		printf ("%lld\n", ans);
	}
}
