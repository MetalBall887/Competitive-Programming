#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Sort all students in ascending order and process dp in a sweepline. d[i][j][k] - the number of ways to assign first i 
//students to teams if there are j groups without the chosen maximum and the overall difference rate is k. For i-th
//student there are 4 possibilities: he'll start and end the group of one person, he'll join to any of "opened" clubs, 
//open a new group or close any of the opened groups.
 
using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
ll d[2][201][2001], n, a[200], k;
 
int main () {
	cin >> n >> k;
 
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
 
	sort (a, a + n);
 
	d[0][0][0] = 1;
	d[0][1][0] = 1;
 
	for (int i = 1; i < n; i++) {
		int b = (i & 1), len = (a[i] - a[i-1]);
 
		memset (d[b], 0, sizeof (d[b]));
 
		for (int j = 0; j <= i; j++) {
			for (int w = 0; w <= k; w++) {
				d[!b][j][w] %= MOD;
				if (w + j * len > k) continue;
				d[b][j][w + j * len] += (j + 1) * d[!b][j][w] % MOD;
				d[b][j+1][w + j * len] += d[!b][j][w];
				if (j) d[b][j-1][w + j * len] += j * d[!b][j][w] % MOD;
			}
		}
 
	}
 
	ll ans = 0;
 
	int b = (n - 1) % 2;
 
	for (int i = 0; i <= k; i++) {
		ans += d[b][0][i];
	}
 
	cout << ans % MOD << endl;
}
