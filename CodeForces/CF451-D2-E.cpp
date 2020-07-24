#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//The idea is, instead of the counting all ways to take flowers where from every box there are at most fi flowers taken, find the opposite: number of ways to
//take flowers where at least from one of the boxes there were fi+1 flowers taken. The "at least from one" part is done by the principle of inclusion-exclusion
//as a union that can be counted from intersections.
 
 
using namespace __gnu_pbds;
 
#define N 100003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
ll inv[100];
 
ll qpow (ll a, ll b) {
	ll s = 1;
	while (b) {
		if (b & 1) s = s * a % MOD;
		b >>= 1;
		a = a * a % MOD;
	}
 
	return s;
}
 
ll c (ll n, ll k) {
	if (k > n || n < 0) return 0;
	ll ans = 1;
 
	ll r = min (k, n - k);
 
	for (ll i = 1; i <= r; i++)
		ans = ans * inv[i] % MOD;
	for (ll i = n - r + 1; i <= n; i++)
		ans = i % MOD * ans % MOD;
 
	return ans;
}
 
int main () {
	ll n, S;
	cin >> n >> S;
 
	ll a[n];
 
	for (int i = 0; i <= n; i++) {
		inv[i] = qpow (i, MOD - 2);
	}
 
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
 
	ll ans = 0;
 
	for (int i = 0; i < (1 << n); i++) {
		ll cur = S;
 
		for (int j = 0; j < n; j++) {
			if ((i >> j) & 1) cur -= a[j] + 1;
		}
		if (__builtin_popcount (i) & 1) ans += MOD - c (cur + n - 1, n - 1);
		else ans += c (cur + n - 1, n - 1);
 
		ans %= MOD;
	}
 
	cout << ans;
}
