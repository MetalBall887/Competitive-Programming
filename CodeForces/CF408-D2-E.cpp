#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
//Let's choose some k stations. If there are some stations between the leftmost and the rightmost that haven't been chosen
//we can try to "move" all stations to the middle that way no gaps are left. That way no distances between any chosen stations
//increase, so the average does not increase as well. That means, any set of stations can be "compressed" to the form of k consequent
//stations without increasing the average, which makes consequent placement optimal. It's only left to create a sliding window
//of length k.
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

ll a[1000000], n, k, psum, pans, ans, ind, sorted[1000000];
 
bool Comp (int i, int j)
{
	return a[i] < a[j];
}

int main ()
{
	cin >> n;

	for (ll i = 0; i < n; i++)
	{
		scanf ("%lld", &a[i]);
		sorted[i] = i;
	}

	sort (sorted, sorted + n, Comp);

	cin >> k;

	for (ll i = 0; i < k; i++)
	{
		pans += i * a[sorted[i]] - psum;
		psum += a[sorted[i]];
	}

	ans = pans;

	for (ll i = 0; i < n - k; i++)
	{
		psum -= a[sorted[i]];
		pans -= psum - (k - 1) * a[sorted[i]];
		pans += (k - 1) * a[sorted[i + k]] - psum;
		psum += a[sorted[i + k]];

		if (pans < ans)
		{
			ans = pans;
			ind = i + 1;
		}
	}

	for (ll i = 0; i < k; i++)
		printf ("%lld ", sorted[ind + i] + 1);
}
