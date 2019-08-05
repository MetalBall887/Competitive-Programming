#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
//Solutions of the equation x^2+y^2=z^2 in integers are triplets ((x^2-y^2)l, 2xyl, (x^2 + y^2)l) but since we need only pairwise
//coprime, we can remove l, getting triplets (x^2 - y^2, 2xy, x^2 + y^2) for integer x and y. We know that all numbers in a must
//be <= m. To keep at least one pair out of one triplet inside our definition range must hold 2xy <= m, because 2xy <= x^2 + y^2 
//(if 2xy > m, then two values are already out of range). So our nested loops with complexity O(xy) are bounded by m. 
//Maintain connected components with DSU.
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
 
const ll MOD = 1e9 + 7, INF = 1e18 + 1;
 
using namespace std;
 
ll a[1000000], cnt, n, m;
ll p[1000000], sz[1000000];
 
int d[10000001];
 
ll gcd (ll a, ll b)
{
	if (!b) return (a > 1);
	else return gcd (b, a % b);
}
 
ll find (ll x)
{
	if (p[x] == x) return x;
	else return p[x] = find (p[x]);
}
 
void unite (ll a, ll b)
{
	a = find (a);
	b = find (b);
 
	if (a == b) return;
 
	if (sz[a] < sz[b]) swap (a, b);
 
	p[b] = a;
	sz[a] += sz[b];
	cnt--;
}
 
int main ()
{
	cin >> n;
 
	for (ll i = 0; i < n; i++)
	{
		p[i] = i;
		sz[i] = 1;
	}
 
	memset (d, -1, sizeof (d));
 
	cnt = n;
 
	for (ll i = 0; i < n; i++)
	{
		scanf ("%lld", &a[i]);
		d[a[i]] = i;
		m = max (m, a[i]);
	}
 
	for (ll y = 0; y <= m; y++)
		for (ll x = y + 1; x * x - y * y <= m && 2 * x * y <= m; x++)
		{
			ll x1 = x * x + y * y;
			ll x2 = 2 * x * y;
			ll x3 = x * x - y * y;
 
			if (gcd (x1, x2) || gcd (x2, x3) || gcd (x1, x3)) continue;
 
			if (x1 <= m && d[x1] >= 0 && d[x2] >= 0) unite (d[x1], d[x2]);
			if (x1 <= m && d[x1] >= 0 && d[x3] >= 0) unite (d[x1], d[x3]);
			if (d[x2] >= 0 && d[x3] >= 0) unite (d[x2], d[x3]);
		}
 
	cout << cnt;
}
