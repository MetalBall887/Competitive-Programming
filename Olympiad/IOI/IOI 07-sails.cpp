#include <bits/stdc++.h>
//https://ioinformatics.org/files/ioi2007solutions.pdf
 
#define N 1000001
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

ll n, m;

struct BIT {
	ll t[N];

	void update (int l, int r) {
		if (l > r) return;
		r++;
		for (; r <= m; r = (r | (r + 1)))
			t[r]--;
		for (; l <= m; l = (l | (l + 1)))
			t[l]++;
	}

	ll get (ll x) {
		ll sum = 0;
		for (; x >= 0; x = (x & (x + 1)) - 1)
			sum += t[x];
		return sum;
	}

	ll upper_bound (ll x) {
		int l = 0, r = m - 1;
		if (get (r) > x) return r + 1;

		while (l < r) {
			int mid = (l + r) / 2;
			if (get (mid) > x) l = mid + 1;
			else r = mid;
		}

		return l;
	}
} t;
pair <ll, ll> a[N];

int main () {
	cin >> n;

	for (ll i = 0; i < n; i++) {
		cin >> a[i].first >> a[i].second;
		m = max (m, a[i].first);
	}

	sort (a, a + n);

	for (ll i = 0; i < n; i++) {
		ll h, k; 
		tie (h, k) = a[i];

		int x = t.get (h - k);
		int l = t.upper_bound (x);
		int r = min (h - 1, t.upper_bound (x - 1) - 1);
		if (r < h) t.update (r + 1, h - 1);
		int p = k - (h - r - 1);
		t.update (l, l + p - 1);
	}

	ll sum = 0;

	for (ll i = 0; i <= m; i++) {
		ll x = t.get (i);
		sum += x * (x - 1) / 2;
	}

	cout << sum;
}
