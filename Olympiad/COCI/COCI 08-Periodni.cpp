#include <bits/stdc++.h>
//For a subhistogram d[i] - the number of ways to distribute i elements in the subhistogram. We can apply a sweeping line
//algorithm going from the top to the bottom, creating new empty histograms in places where columns start. If the sweeping line
//is at the place where column starts, we want to merge it with histograms on the left and on the right, if any. Merge is:
//d[n] = sum over i d_left_hist[i]*d_right_hist[n-i]. Also through the sweeping line, when we need to merge histograms, we
//need their current d[i] values by heightening them by (last height) - (current height) with a rectangle h*width_of_histogram.
//d[n] in this way will be: suppose there were i elements in old histogram and we want to distribute j more in the rectangle.
//i columns will be already inaccessible, so the formula will be C[w-i][j]*C[h][j]*(j! as the number of bijections between chosen
//columns and rows). We need to actualize histograms only when merging, we need to merge only when a new column appears in 
//the sweeping line, so the number of merges and actualizations is O(n). Thus the algoritm works in O(n^3).
 
#define N 1000001
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int p[1000], n, k, h[1000], fact[N], inv_fact[N];

vector < pair <int, int> > v;

ll C (int n, int k) {
	return (ll)fact[n] * inv_fact[k] % MOD * inv_fact[n-k] % MOD;
}

ll qpow (ll a, ll b) {
	ll s = 1;

	while (b) {
		if (b & 1) s = s * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}

	return s;
}

struct histogram {
	vector <ll> d;
	int last, w;

	histogram () : last (0), w (0) {}
	histogram (int x, int w) : last (x), d (vector <ll> (w + 1)), w (w) {
		d[0] = 1;
	}

	void actualize (int x) {
		if (last == x) return;
		vector <ll> new_d (w + 1);
		for (int i = 0; i <= w; i++) {
			for (int j = 0; j <= min (w - i, last - x); j++) {
				new_d[i + j] += (ll) d[i] * C (last - x, j) % MOD * C (w - i, j) % MOD * fact[j] % MOD;
				if (new_d[i + j] >= MOD) new_d[i + j] -= MOD;
			}
		}

		d = move (new_d);

		last = x;
	}
} d[1000];

int find (int x) {
	if (p[x] == x) return x;
	return p[x] = find (p[x]);
}

void merge (int x, int y, int h) {
	x = find (x), y = find (y);
	auto& a = d[x];
	auto& b = d[y];
	histogram c (h, a.w + b.w);
	a.actualize (h), b.actualize (h);
	c.d[0] = 0;

	for (int i = 0; i <= a.w; i++)
		for (int j = 0; j <= b.w; j++) {
			c.d[i + j] += (ll) a.d[i] * b.d[j] % MOD;
			if (c.d[i + j] >= MOD) c.d[i + j] -= MOD;
		}

	p[y] = x;
	d[x] = c;
}

int main () {
	cin >> n >> k;

	inv_fact[0] = fact[0] = 1;
	for (int i = 1; i < N; i++) {
		fact[i] = (ll) i * fact[i-1] % MOD;
	}

	inv_fact[N - 1] = qpow (fact[N - 1], MOD - 2);
	for (int i = N - 1; i > 0; i--) {
		inv_fact[i-1] = (ll) i * inv_fact[i] % MOD;
	}

	for (int i = 0; i < n; i++) {
		p[i] = i;
		cin >> h[i];

		v.push_back ({-h[i], i});
	}

	sort (v.begin(), v.end());

	for (auto x : v) {
		d[x.second] = histogram (-x.first, 1);
		if (x.second && d[find (x.second - 1)].w) {
			merge (x.second - 1, x.second, -x.first);
		}

		if (x.second + 1 < n && d[find (x.second + 1)].w) {
			merge (x.second, x.second + 1, -x.first);
		}
	}
	auto ans = d[find (0)];
	ans.actualize (0);

	cout << ans.d[k];
}
