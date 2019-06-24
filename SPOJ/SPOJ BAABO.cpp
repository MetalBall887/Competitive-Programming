#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
#include <algorithm>
//The main observation: if we can create a new pair in our matching, then it's not optimal.
//that means, if our matching is (ai, bi) 0 < i <= n and for some i > 1 (ai - ai-1 > 1 && bi - bi-1 > 1) then we can add 
//a new pair in that gap and increase the profit => this matching is not optimal. That means, in an optimal matching 
//for each (ai, bi) ai = ai-1 + 1 or bi = bi-1 + 1. Let dp[i][j] will be the answer for first i elements of A 
//and first j of B, such way i or j is included in the matching.
//dp[i][j] = max (max (dp[i-1][k-1] + ai*bk - (bk+1 + bk+2 +...+ bj) ^ 2, dp[k-1][j-1] + ak*bj - (ak+1 + ak+2 +...+ ai) ^ 2)
//let sa[i] = a1 + a2 +...+ ai. Then (ak+1 + ak+2 +...+ ai) ^ 2 = (sa[i] - sa[k]) ^ 2 = sa[i] ^ 2 - 2sa[i]sa[k] + sa[k] ^ 2
//So we can make a f_ik(x) = -2sa[k]*x + sa[k] ^ 2 - dp[i-1][k-1] - a[i-1][k-1], same for j. Then
//dp[i][j] = - sa[i] ^ 2 - min (f_ik(sa[i]), f_kj(sb[j])), so we can apply a Convex Hull Trick.
//dp[n][n] is the answer, because if we can make a pair from An and Bn, our matching is not optimal due to the main observation.
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

struct line
{
	ll k, b;

	ll eval (ll x)
	{
		return k * x + b;
	}
};

vector <line> row[5000], col[5000];
ll n;

double intersect (line a, line b)
{}

bool bad (line a, line b, line c)
{
	return (a.b - c.b) * (c.k - b.k) >= (b.b - c.b) * (c.k - a.k);
}

void add_line (vector <line> &cht, line a)
{
	while (cht.size () >= 2 && bad (cht[cht.size () - 2], cht.back (), a))
		cht.pop_back ();
	cht.push_back (a);
}

ll get_min (vector <line> &cht, ll x)
{
	if (cht.size () == 1 || x <= intersect (cht[0], cht[1])) return cht[0].eval (x);

	ll l = 0, r = cht.size () - 2;

	while (l < r)
	{
		ll mid = (l + r + 1) / 2;
		if (intersect (cht[mid], cht[mid + 1]) <= x) l = mid;
		else r = mid - 1;
	}

	return cht[l + 1].eval (x);
}

ll a[2000], b[2000], sa[2000], sb[2000], dp[2000][2000];

int main ()
{
	cin >> n;

	for (ll i = 0; i < n; i++)
	{
		scanf ("%lld", &a[i]);
		sa[i] = a[i] + (i ? sa[i-1] : 0);
	}

	for (ll i = 0; i < n; i++)
	{
		scanf ("%lld", &b[i]);
		sb[i] = b[i] + (i ? sb[i-1] : 0);
	}

	for (ll i = 0; i <= n; i++)
		for (ll j = 0; j <= n; j++)
		{
			if (!i && !j) continue;
			if (j == 0) dp[i][j] = -sa[i-1] * sa[i-1];
			else if (i == 0) dp[i][j] = -sb[j-1] * sb[j-1];
			else
			{
				add_line (col[j], {-2LL * sa[i-1], sa[i-1] * sa[i-1] - a[i-1] * b[j-1] - dp[i-1][j-1]});
				add_line (row[i], {-2LL * sb[j-1], sb[j-1] * sb[j-1] - a[i-1] * b[j-1] - dp[i-1][j-1]});

				dp[i][j] = - sa[i-1] * sa[i-1] - get_min (col[j], sa[i-1]);
				dp[i][j] = max (dp[i][j], - sb[j-1] * sb[j-1] - get_min (row[i], sb[j-1]));
			}
		}

	cout << dp[n][n];
}
