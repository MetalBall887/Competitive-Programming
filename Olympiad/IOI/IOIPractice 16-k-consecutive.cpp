#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//For each k-consecutive permutation there is a unique minimal partition into consecutive subarrays such that if we order
//these subarrays lexicographically, no two adjacent subarrays will be "near" in lexicographic order. For example, 
//for 1 7 5 6 2 3 4 that will be (1) (7) (5 6) (2 3 4). So for each partition with all subarrays not longer than k we can 
//count the number of permutations of these subarrays to get the number of k-consecutive permutations. To find the number of
//partitions we use the dp table f[i][j] - the number of partitions for i elements into j subarrays, where each subarray is 
//not longer than k. f[i][j] = f[i-1][j-1] + f[i-2][j-1] + ... + f[i-k][j-1], which can be computed quickly with prefix sums.
//So for each such partition of size i we want to solve the problem for k = 1. Let's call an adjacent pair in permutation bad
//if their values differ by one and the second value is bigger. d[i][j] - the number of permutations of i elements with j
//bad pairs. Let's say if we append a value x to permutation, all values >= x before will be increased by one. That means,
//for each bad pair (i, i+1) we can take x = i+1 and break down the pair (notice that we can break down at most one pair), 
//we can take the last value + 1 (we don't break down a bad pair with that, only creating a new one) and other choices 
//don't change the number of pairs. So the recursion will be d[i][j] = (j+1)d[i-1][j+1](j+1 ways to choose a bad pair to 
//break) + d[i-1][j-1] (create a pair) + (i - j - 1)*d[i-1][j](other options).
 
using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

ll d[5001][5001], f[5001][5001], n, k;
 
int main () {
	cin >> n >> k;

	d[1][0] = 1;

	for (int i = 2; i <= n; i++)
		for (int j = 0; j < i; j++) {
			d[i][j] = (j + 1) * d[i-1][j+1];
			d[i][j] += (i - j - 1) * d[i-1][j];
			if (j) d[i][j] += d[i-1][j-1];
			d[i][j] %= MOD;
		}

	f[0][0] = 1;

	for (int i = 1; i <= n; i++)
		f[i][0] = 1;

	for (int j = 1; j <= n; j++)
		for (int i = 1; i <= n; i++) {
			f[i][j] = f[i-1][j-1];
			if (i - k > 0) f[i][j] += MOD - f[i-k-1][j-1];
			f[i][j] += f[i-1][j]; 
			f[i][j] %= MOD;
		}

	ll ans = 0;

	for (int i = 1; i <= n; i++) {
		ans += (f[n][i] + MOD - f[n-1][i]) % MOD * d[i][0];
		ans %= MOD;
	}

	cout << ans << endl;
}
