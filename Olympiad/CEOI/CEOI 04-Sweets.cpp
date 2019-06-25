#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
#include <algorithm>
//First, we use Stars-and-Bars method, but with a spare bar to isolate a number of stars that won't be the part of any number.
//With that, the number of groups of numbers with size k and sum <= n is C[n + k][k] (if order matters). But here we have
//limits for each number. We can assume that some subset of numbers is exceeding their limits, constantly adding mi + 1 for 
//number ai that should exceed its limit. Then the number of ways is C[n + k - (mi1 + 1) - (mi2 + 1) - ...][k]. So we can
//find answer for some subset of numbers to be bigger then thier limits at once (intersection of sets i1, i2, ...), so
//we can find a union of these sets by inclusion-exclusion principle. C[n][k] can be relatively quickly
//computed by representing it as a fraction (n-k+1)(n-k+2)...n/1*2*...*k and simplifying this fraction in O(k^2logk).
//Overall complexity is O(2^nn^2logn).
#include <bitset>
#include <queue>
#include <math.h>
#include <stack>
#include <vector>
#include <string.h>
 
typedef long long ll;
typedef long double ld;
 
const ll MOD = 2004, INF = 1e18 + 1;
 
using namespace std;

int n, m[12], a, b;
int ans_a, ans_b;

int C (int n, int k)
{
	vector<ll> q, b;
	for (int i = n - k + 1; i <= n; i++)
		q.push_back (i);

	for (int i = 1; i <= k; i++)
	{
		int s = i;

		for (int j = 2; j <= i; j++)
			while (s % j == 0)
			{
				s /= j;
				b.push_back (j);
			}
	}

	for (int i : b)
	{
		for (int j = 0; j < q.size (); j++)
			if (q[j] % i == 0)
			{
				q[j] /= i;
				break;
			}
	}

	ll sum = 1;

	for (ll a : q)
		sum = sum * a % MOD;
	return sum;
}

int main ()
{
	cin >> n;
	cin >> a >> b;

	for (int i = 0; i < n; i++)
		scanf ("%d", &m[i]);
	for (int mask = 0; mask < (1 << n); mask++)
	{
		int sum = b, odd = 0;
		for (int i = 0; i < n; i++)
			if ((1 << i) & mask)
			{
				odd++;
				sum -= m[i] + 1;
			}

		if (sum < 0) continue;

		if (odd & 1) ans_b += MOD - C (sum + n, n);
		else ans_b += C (sum + n, n);
		if (ans_b >= MOD) ans_b -= MOD;
	}

	for (int mask = 0; mask < (1 << n); mask++)
	{
		int sum = a - 1, odd = 0;
		for (int i = 0; i < n; i++)
			if ((1 << i) & mask)
			{
				odd++;
				sum -= m[i] + 1;
			}

		if (sum < 0) continue;

		if (odd & 1) ans_a += MOD - C (sum + n, n);
		else ans_a += C (sum + n, n);
		if (ans_a >= MOD) ans_a -= MOD;
	}

	cout << (ans_b - ans_a + MOD) % MOD << endl;
}
