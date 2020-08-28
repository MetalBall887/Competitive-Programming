#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//Let d be our new gcd, x = kd. For each numbers [(k-1)d+1;kd] they either add enough times to become x or get deleted. For this segment it's easy to determine a
//border where it gets more optimal to delete a number rather than increase it to x. For each number i to the right it will cost (x - i)*y, if a[l..r] is the
//number of elements from l to r and s[l..r] is the sum of elements from l to r it will be a[x-k;x]*x*y - b[x-k;x]*y. For each such x try all divisors and
//add correspondent cost to the answer if new gcd is the current divisor of x.
 
//using namespace __gnu_pbds;
 
#define N 2000001
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
ll p[N + 1], p2[N + 1], s[N + 1], ans[N + 1], n, x, y;
 
vector <int> dv[N + 1];
 
ll sum (int l, int r) {
	if (l > r) return 0;
	return p[r] - p[l-1];
}
 
ll sum2 (int l, int r) {
	if (l > r) return 0;
	return p2[r] - p2[l-1];
}
 
int main () {
	ios::sync_with_stdio(0);
	cin.tie(0);
 
	cin >> n >> x >> y;
 
	int mx = 0;
 
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		mx = max (mx, a);
		s[a]++;
		p[a] -= a;
	}
 
	for (int i = 1; i <= 2 * mx; i++) {
		p2[i] = s[i] + p2[i-1];
		p[i] += p[i-1];
	}
 
	for (int i = 2; i <= 2 * mx; i++) {
		if (!dv[i].empty ()) {
			ans[i] = 1e18;
			continue;
		}
		for (int j = i; j <= 2 * mx; j += i) {
			dv[j].push_back (i);
		}
	}
 
	int k = x / y;
 
	for (int i = 2; i <= 2 * mx; i++) {
		for (int d : dv[i]) {
			int l = i - d + 1, r = i, m = max (l, i - k);
			ll c = x * sum2 (l, m - 1) + y * (sum (m, r) + sum2(m, r) * r);
			ans[d] += c;
		}
	}
 
	cout << *min_element (ans + 2, ans + 2 * mx + 1);
}
