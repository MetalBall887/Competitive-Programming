#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//The main idea of this solution is to keep a data structure with queue sizes sorted where we can perform range updates. Since we're changing sizes at most by 1,
//we can keep the array sorted.
 
using namespace __gnu_pbds;
 
#define N 2000001

using namespace std;


typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int n, a[N], p[N], q, g[N];

struct BIT {
	int t[N];

	void update (int x, int d) {
		for (; x <= n; x = (x | (x + 1)))
			t[x] += d;
	}

	int get (int r) {
		int sum = 0;

		for (; r >= 0; r = (r & (r + 1)) - 1)
			sum += t[r];

		return sum;
	}
} t;

int main () {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> q;

	for (int i = 0; i < n; i++) {
		cin >> a[i];
		p[i] = i;
	}

	sort (p, p + n, [&](int i, int j) { return a[i] < a[j]; });
	sort (a, a + n);

	for (int i = 0; i < n; i++) {
		g[p[i]] = i;
		t.update (i, a[i]), t.update (i + 1, -a[i]);
	}

	for (int i = 0; i < q; i++) {
		int v, a;
		cin >> v >> a;

		if (v == 1) {
			a--;

			int l = 0, r = n - 1;

			while (l < r) {
				int mid = (l + r + 1) / 2;

				if (t.get (mid) <= t.get (g[a])) l = mid;
				else r = mid - 1;
			}

			int px = a, py = p[r];
			swap (g[px], g[py]);
			swap (p[g[px]], p[g[py]]);
			t.update (g[px], 1);
			t.update (g[px] + 1, -1);
		} else if (v == 2) {

			int l = 0, r = n;

			while (l < r) {
				int mid = (l + r) / 2;

				if (t.get (mid) < a) l = mid + 1;
				else r = mid;
			}

			cout << n - l << '\n';
		} else {
			int l = 0, r = n - 1;

			while (l < r) {
				int mid = (l + r) / 2;
				if (t.get (mid) < a) l = mid + 1;
				else r = mid;
			}

			t.update (l, -1);
		}
	}
}
