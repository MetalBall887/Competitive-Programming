#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//We can find for each column from which position it is watered and fertilized and observe monotonicity for both. Then, for
//each pair of columns we can find the upmost and downmost points of rectangles (they will be on the fertilization and watering
//points of leftmost and the rightmost columns accordingly). The formula for counting the number of rectangles between each 
//pair of columns looks like this (a - b) * (a - b + 1) / 2, which can be breaken down to a*(a+1)/2+b*(b-1)/2-ab, which can
//be can be grouped and for each right column we can maintain the set of left columns and some middle values like b*(b-1)/2
//also grouped in one sum, so that all the formulas can be computed for all accessible left columns at once.
 
using namespace __gnu_pbds;
 
#define N 1000001
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

ll n, w[N], f[N], a[N], ans;
 
int main () {
	freopen ("sprinklers.in", "r", stdin);
	freopen ("sprinklers.out", "w", stdout);

	cin >> n;

	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		a[x] = y;
	}

	for (int i = 0; i < n; i++) {
		w[i] = (i == 0 ? a[i] : min (w[i-1], a[i]));
	}

	for (int i = n - 1; i >= 0; i--) {
		f[i] = (i == n - 1 ? a[i] : max (f[i+1], a[i]));
	}

	ll sum_k = 0, sum_kk = 0;

	int l = 0, r = 0;

	for (int i = 0; i < n; i++) {
		if (r < i) {
			sum_k += w[r];
			sum_kk += w[r] * (w[r] - 1) % MOD;
			sum_k %= MOD, sum_kk %= MOD;
			r++;
		}
		while (l < r && w[l] >= f[i]) {
			sum_k += MOD - w[l];
			sum_kk += MOD - w[l] * (w[l] - 1) % MOD;
			sum_k %= MOD, sum_kk %= MOD;
			l++;
		}

		ans += (r - l) * (f[i] + 1) % MOD * f[i] % MOD;
		ans += sum_kk;
		ans += MOD - 2 * f[i] * sum_k % MOD;
		ans %= MOD;
	}

	cout << ans * 500000004 % MOD;
}
