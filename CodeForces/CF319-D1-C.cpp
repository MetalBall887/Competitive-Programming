#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
//first, notice that bn = 0, so we need to cut the last tree, but after cutting the last tree we can cut all other trees
//for free, so our goal is to cut the last tree as soon as possible. b is decreasing, so after cutting some tree
//it's not optimal to cut trees on the left, so we can just cut trees from left to right until we've cut the last one.
//for dp[i] (min time to cut i-th tree) we need to find k - p[timal previous tree we'd cut right before i-th
//do get its b. so we need to find such j, b[j]*a[i]+dp[j] = min put of all j < i. we can keep a set of lines
//and construct a convex hull on it to find min on every point.
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
 
int n, ptr;
ld dp[1000000], a[1000000], b[1000000];

struct line
{
	ld k, b;
};

vector <line> cht;

double intersect (line a, line b)
{
	return (b.b - a.b) / (a.k - b.k);
}

ld eval (line l, ld x)
{
	return l.k * x + l.b;
}

void add (line a)
{
	while (ptr >= 2 && intersect (cht[ptr-2], a) <= intersect (cht[ptr-2], cht[ptr-1]))
	{
		cht.pop_back ();
		ptr--;
	}

	cht.push_back (a);
	ptr++;
}

ld find_min (ld x)
{
	if (ptr == 1 || x <= intersect (cht[0], cht[1])) return eval (cht[0], x);

	int l = 0, r = ptr - 2;

	while (l < r)
	{
		int mid = (l + r + 1) / 2;

		if (intersect (cht[mid], cht[mid + 1]) <= x) l = mid;
		else r = mid - 1;
	}

	return eval (cht[l + 1], x);
}

int main ()
{
	cin >> n;

	for (int i = 0; i < n; i++)
		scanf ("%Lf", &a[i]);

	for (int i = 0; i < n; i++)
		scanf ("%Lf", &b[i]);

	add ({b[0], (ld) 0.0});

	for (int i = 1; i < n; i++)
	{
		dp[i] = find_min (a[i]);

		add ({(ld) b[i], (ld) dp[i]});
	}

	cout << (ll) dp[n-1];
}
