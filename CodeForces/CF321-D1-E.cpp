#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
#include <algorithm>
//let d[i][j] = the minimal possible level of unfamiliarness between first i foxes
//placed on j gondolas. Also let p[i][j] = the minimal possible value that denotes
//the last fox that isn't placed in the last gondola. Or the minimal k, so foxes from k + 1 to j
//can be placed in an ith gondola and it's still possible to det d[i][j] as an answer for i and j
//it can be shown that p[i][j] <= p[i][j + 1] and 0 <= p[i][j] <= n - 1, so all p[i][j] are points on 
//a coordinate line. If we have p[i][l] and p[i][r] computed, we may only look for values between those two
//for p[i][mid], l < mid < r, what makes it possible to add divide-and-conquer by choosing 
//mid = (l + r) / 2. Complexity: O(NKlogN).
//Technique is called D&C dp optimisation.
#include <bitset>
#include <queue>
#include <math.h>
#include <stack>
#include <vector>
#include <string.h>
 

inline int get ()
{
#ifdef _WIN32
	return _getchar_nolock ();
#else
	return getchar_unlocked ();
#endif
}
 
int read ()
{
	int ret = 0, chr = get (), m = 0;
	while (isspace (chr)) chr = get ();
	while (chr == '-' || isdigit (chr)) 
	{
		if (chr == '-') m = 1;
		else ret = 10LL * ret + chr - '0';
		chr = get ();
	}
 
	return (m ? -ret : ret);
}

typedef long long ll;
 
const ll MOD = 1e9 + 7, INF = 1e18 + 1;
 
using namespace std;

int C[4000][4000], d[800][4000], n, u[4000][4000], k;

int count (int i, int k, int j)
{
	return d[i-1][k] + C[k + 1][j];
}

void Rec (int k, int l, int r, int optl, int optr)
{
	if (l > r) return;

	int mn = optl;

	int mid = (l + r) / 2;

	for (int i = optl; i <= min (mid - 1, optr); i++)
	{
		if (count (k, i, mid) < count (k, mn, mid)) mn = i;
	}

	d[k][mid] = count (k, mn, mid);

	Rec (k, l, mid - 1, optl, mn);
	Rec (k, mid + 1, r, mn, optr);
}

int main ()
{
	cin >> n >> k;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			u[i][j] = read ();
			if (j) u[i][j] += u[i][j-1];
		}

	for (int k = 1; k < n; k++)
		for (int i = 0; i + k < n; i++)
			C[i][i + k] = C[i + 1][i + k] + u[i][i + k] - u[i][i];

	for (int i = 0; i < n; i++)
		d[0][i] = C[0][i];

	for (int i = 1; i < k; i++)
		Rec (i, 0, n - 1, 0, n - 1);

	cout << d[k-1][n-1];
}
