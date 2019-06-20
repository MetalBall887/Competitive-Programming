#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
//Observation 1: if we sort an array of strings in lexicographical order, largest common prefix of two strings is a largest
//common prefix of these two strings and all strings between them (LCP (s[l], ..., s[r]) = LCP (s[l], s[r])).
//Observation 2: if LCP (s[l], s[l+1], ..., s[r]) = x, then there exists l <= l1 < r1 <= r where LCP (s[l1], ... s[r1]) = x.
//Same for l1, r1 and l2, r2 and so on. So if LCP (s[l], ..., s[r]) = x, there exists such l <= m <= r, 
//LCP (s[m], s[m+1]) = x. So let's solve our problem on a segments of a sorted array. d[l][r][k] is the maximum value on
//[l;r] with k strings selected. For each such [l;r] find the point m described above, because from observ. 1 for each
// l <= i <= m and m < j <= r LCP(s[i], s[j]) = LCP (s[l], s[r]). So if k1 is the number of strings selected on segment [l;m]
//and k2 - on segment [m+1;r], d[l][r][k] = max k1, k2, k1 + k2 = k (d[l][m][k1] + d[m + 1][r][k2], lcp[l][r] * k1 * k2)
//So we can run a recursive dynamic for this. the time complexity for it is T(n) = T(k) + T(n-k) + k * (n - k).
//It reaches maximum at k = n / 2, T(n) = 2 * T(n / 2) + n^2/4, which is O(n^2).
#include <map>
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

vector <ll> d[2000][2000];

ll lcp[2000][2000], n, k, u[2000][2000];

string s[2000];

void Rec (ll l, ll r)
{
	if (u[l][r]) return;
	u[l][r] = 1;

	vector <ll> v (r - l + 2);

	if (l == r) 
	{
		d[l][r] = v;
		return;
	}

	ll mid = l;

	for (ll i = l; i <= r - 1; i++)
		if (lcp[i][i + 1] == lcp[l][r]) mid = i;

	Rec (l, mid);
	Rec (mid + 1, r);

	for (ll i = 0; i <= mid - l + 1; i++)
		for (ll j = 0; j <= r - mid; j++)
			v[i + j] = max (v[i + j], lcp[l][r] * i * j + d[l][mid][i] + d[mid + 1][r][j]);

	d[l][r] = v;

	return;
}

int main ()
{
	cin >> n >> k;

	for (ll i = 0; i < n; i++)
	{
		cin >> s[i];
	}

	sort (s, s + n);

	for (ll i = 0; i < n; i++)
	{
		lcp[i][i] = s[i].size ();

		for (ll j = n - 1; j > i; j--)
		{
			if (j < n - 1) lcp[i][j] = lcp[i][j + 1];
			
			while (lcp[i][j] <= min (s[i].size (), s[j].size ()) && s[j][lcp[i][j]] == s[i][lcp[i][j]])
				lcp[i][j]++;
			if (lcp[i][j] > min (s[i].size (), s[j].size ())) lcp[i][j]--;
		}
	}

	Rec (0, n - 1);

	cout << d[0][n - 1][k];
}
