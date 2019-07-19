#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
//dp on profile. dp[i][(a, b, c)] - the number of ways to create a broken line that connects all points from column 
//i back to column i that way, degrees of points (i, 0), (i, 1), (i, 2) would be a, b, c correspondingly. The number 
//of non-zero statesis actually not big, because for every state there should be two points with degree 1 
//(start and end of the broken line). So we can figure out all the states by simply drawing, for example. For the last
//subtask matrix expo optimisation required.
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
 
const ll MOD = 1e9, INF = 1e18 + 1;
 
using namespace std;

ll d[1000000][3][3][3], n;

ll tr (ll a, ll b, ll c)
{
	return 9 * a + 3 * b + c;
}

struct Matrix
{
	ll a[27][27];

	Matrix ()
	{
		memset (a, 0, sizeof (a));
	}

	Matrix (int s)
	{
		memset (a, 0, sizeof (a));

		for (int i = 0; i < 27; i++)
			a[i][i] = 1;
	}
};

Matrix mult (Matrix a, Matrix b)
{
	Matrix s;

	for (int i = 0; i < 27; i++)
		for (int j = 0; j < 27; j++)
			for (int k = 0; k < 27; k++)
				s.a[i][j] = (s.a[i][j] + a.a[i][k] * b.a[k][j] % MOD) % MOD;

	return s;
}

Matrix qpow (Matrix a, ll b)
{
	Matrix s (1);

	while (b)
	{
		if (b & 1) s = mult (s, a);
		b >>= 1;
		a = mult (a, a);
	}

	return s;
}

int main ()
{
	cin >> n;

	Matrix st;

	st.a[0][tr (1, 2, 1)] = 1;
	st.a[0][tr (1, 1, 0)] = 1;
	st.a[0][tr (0, 1, 1)] = 1;

	Matrix pow;
	
	pow.a[tr (1, 2, 1)][tr (0, 1, 1)] = 1;
	pow.a[tr (1, 1, 2)][tr (0, 1, 1)] = 1;
	pow.a[tr (2, 1, 1)][tr (0, 1, 1)] = 1;

	pow.a[tr (1, 2, 1)][tr (1, 0, 1)] = 1;
	pow.a[tr (1, 1, 2)][tr (1, 0, 1)] = 1;
	pow.a[tr (2, 1, 1)][tr (1, 0, 1)] = 1;

	pow.a[tr (1, 2, 1)][tr (1, 1, 0)] = 1;
	pow.a[tr (1, 1, 2)][tr (1, 1, 0)] = 1;
	pow.a[tr (2, 1, 1)][tr (1, 1, 0)] = 1;

	pow.a[tr (1, 0, 1)][tr (1, 1, 2)] = 1;
	pow.a[tr (1, 2, 1)][tr (1, 1, 2)] = 1;
	pow.a[tr (1, 1, 2)][tr (1, 1, 2)] = 1;
	pow.a[tr (2, 1, 1)][tr (1, 1, 2)] = 1;

	pow.a[tr (2, 1, 1)][tr (1, 2, 1)] = 2;
	pow.a[tr (1, 2, 1)][tr (1, 2, 1)] = 2;
	pow.a[tr (1, 1, 2)][tr (1, 2, 1)] = 2;
	pow.a[tr (1, 1, 0)][tr (1, 2, 1)] = 1;
	pow.a[tr (0, 1, 1)][tr (1, 2, 1)] = 1;

	pow.a[tr (1, 0, 1)][tr (2, 1, 1)] = 1;
	pow.a[tr (1, 2, 1)][tr (2, 1, 1)] = 1;
	pow.a[tr (1, 1, 2)][tr (2, 1, 1)] = 1;
	pow.a[tr (2, 1, 1)][tr (2, 1, 1)] = 1;

	Matrix fin = mult (st, qpow (pow, n - 1));

	cout << (fin.a[0][tr (1, 1, 2)] + fin.a[0][tr (2, 1, 1)] - fin.a[0][tr (1, 0, 1)] + MOD) % MOD;
}
