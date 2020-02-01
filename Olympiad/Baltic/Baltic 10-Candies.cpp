#include <bits/stdc++.h>
//First of all, we can observe that after each addition in a knapsack problem the number of achieved values can increase almost
//twice. Also by setting this value large enough, we can increase it exactly twice. That means, we should for each candie box
//consider the number of candies achievable by other boxes * 2. For those reasons we need a knapsack dp table, with which we'll
//be able to perform rollbacks. For that, we can keep the number of of ways to achieve this sum modulo some big prime. As
//we know, dp[i+1][j] = dp[i][j] + dp[i][j-x], so, in order to find dp[i] out of dp[i+1], dp[i][j] = dp[i+1][j] - dp[i][j-x].
//If the modulo is 0, there is a high probability the actual value is 0 as well. That way we found needed box to be changed
//but didn't find the minimal new value. For this, we need to find the first value that isn't a difference of two achievable
//sums of boxes without the changed one. So it's {X - Y | X and Y that are combinations of boxes without the changed one}
//Apply knapsack dp substracting all possible combinations of Y from set X (already calculated).
 
#define N 1000001
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
pair <int, int> d[N], rb[N];
bitset <700001> bm, bc;
int b[100], n;
 
int main () {
	cin >> n;
 
	for (int i = 0; i < n; i++) {
		cin >> b[i];
	}
 
	int sum = 0;
 
	d[0] = {1, 1};
 
	sort (b, b + n);
 
	for (int i = 0; i < n; i++) {
		for (int j = sum; j >= 0; j--) {
			if (d[j].first) d[j + b[i]].first = (d[j + b[i]].first + d[j].first) % MOD;
			if (d[j].second) d[j + b[i]].second = (d[j + b[i]].second + d[j].second) % MOD2;
		}
		sum += b[i];
	}
 
	int mx = 0, ind = 0;
 
	for (int i = 0; i < n; i++) {
		int cnt = 0;
		for (int j = 0; j <= sum; j++) {
			rb[j] = d[j];
			if (j >= b[i]) {
				rb[j].first = (rb[j].first + MOD - rb[j - b[i]].first) % MOD;
				rb[j].second = (rb[j].second + MOD2 - rb[j - b[i]].second) % MOD2;
			}
 
			if (rb[j] != make_pair (0, 0)) {
				cnt++;
			}
		}
 
		if (mx < cnt) ind = i, mx = cnt;
	}
 
	for (int j = 0; j <= sum; j++) {
		rb[j] = d[j];
		if (j >= b[ind]) {
			rb[j].first = (rb[j].first + MOD - rb[j - b[ind]].first) % MOD;
			rb[j].second = (rb[j].second + MOD2 - rb[j - b[ind]].second) % MOD2;
		}
 
		bm[j] = (rb[j] != make_pair (0, 0));
	}
 
	cout << b[ind] << ' ';
	
	for (int i = 0; i < n; i++) {
		if (i != ind) bm |= (bm >> b[i]);
	}
 
	for (int i = 0; i <= sum; i++) {
		if (!bm[i]) {
			cout << i << endl;
			return 0;
		}
	}
 
	cout << sum + 1 << endl;
}
