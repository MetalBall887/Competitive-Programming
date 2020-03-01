#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//We will solve this problem with DSU approach. Inside of each cloud if there is a number in qi, that means there 
//should be some pj inside of the cloud to place there, we'll call it "demand", for every pi inside this cloud 
//there should be a qj where we should transfer the element, we'll call it "offer". For each number we'll generate
//a random token and in hash of a specific cloud we'll contribute (offer of x in cloud - demand of x in cloud)*token_x. 
//Not difficult to see that if the cloud is good, its hash is 0. The probability of a hash of the bad cloud being zero
//is small. We also can see that for two clouds the hash of the union is actually the sum of their hashes, so if the union
//of two bad clouds x and y is good, hash_x = -hash_y. We can answer the queries and maintain updates if we keep the sum
//of sizes of clouds with certain hash in a table.
 
using namespace __gnu_pbds;
 
#define N 1000001
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

ll p[N], sz[N], n, pw[N];

ll ans, cnt;

gp_hash_table <ll, ll> ht;
ll h[N];

void change (int x, ll d) {
	if (h[x]) ans -= sz[x] * ht[-h[x]];
	ht[h[x]] -= sz[x];
	if (!d) return;
	h[x] += d;

	if (h[x]) ans += sz[x] * ht[-h[x]];
	ht[h[x]] += sz[x];
}

int find (int x) {
	if (p[x] == x) return x;
	return p[x] = find (p[x]);
}

void unite (int a, int b) {
	a = find (a), b = find (b);
	if (a == b) return;

	p[b] = a;

	if (h[a]) ans -= sz[a] * ht[-h[a]];
	ht[h[a]] -= sz[a];

	h[a] += h[b];
	sz[a] += sz[b];

	if (h[a]) ans += sz[a] * ht[-h[a]];
	ht[h[a]] += sz[a];

	change (b, 0);
	cnt--;
}

ll q, a[N], s[N], rn[N];

int main () {
	ios::sync_with_stdio (0);
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	cin >> n >> q;

	for (int i = 0; i < n; i++) {
		cin >> a[i];
		s[i] = a[i];
	}

	sort (s, s + n);

	for (int i = 1; i <= n; i++) {
		rn[i] = uniform_int_distribution<ll>(0, (1LL << 62))(rng);
	}

	for (int i = 0; i < n; i++) {
		p[i] = i, sz[i] = 1;
		h[i] = rn[a[i]] - rn[s[i]];
		ht[h[i]]++;
	}

	for (int i = 0; i < n; i++) {
		if (h[i] > 0) ans += ht[-h[i]];
	}

	cnt = n;

	for (int i = 0; i < q; i++) {
		int t, x, y;
		cin >> t;

		if (t == 2) {
			cin >> x >> y;
			x--, y--;
			unite (x, y);
		}

		if (t == 1) {
			cin >> x >> y;
			x--, y--;
			int px = find (x), py = find (y);

			change (px, -rn[a[x]]);
			change (py, -rn[a[y]]);

			swap (a[x], a[y]);
			
			change (px, rn[a[x]]);
			change (py, rn[a[y]]);
		}

		if (t == 3) {
			if (ht[0] == n) cout << "DA\n";
			else cout << "NE\n";
		}

		if (t == 4) {
			cout << ans << '\n';
		}
	}
}
